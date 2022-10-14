#include "QueryEvaluator.h"

#include <string>
#include <memory.h>

#include "Query.h"
#include "relation/Rel.h"
#include "ResultExtractor.h"
#include "query_result/Table.h"
#include "query_result/EmptyTable.h"
#include "query_result/WildcardTable.h"
#include "clause_grouper/ClauseGrouper.h"
#include "clause_grouper/SimpleClauseGrouper.h"
#include "clause_grouper/OptimizedClauseGrouper.h"

using std::vector;
using std::shared_ptr;
using std::string;


QueryEvaluator::QueryEvaluator(Query query) {
	query_ = query;
	data_retriever_ = DataRetriever();
};

QueryEvaluator::QueryEvaluator(Query query, DataRetriever data_retriever) {
	query_ = query;
	data_retriever_ = data_retriever;
}


bool QueryEvaluator::Evaluate() {
	shared_ptr<vector<shared_ptr<Ref>>> select_tuple = query_.GetSelectTuple();
	
	std::vector<shared_ptr<Clause>> clauses = *query_.GetAllClauses();

	//shared_ptr<ClauseGrouper> clause_grouper = std::make_shared<SimpleClauseGrouper>(clauses, query_.GetSelectSynonyms());
	shared_ptr<ClauseGrouper> clause_grouper = std::make_shared<OptimizedClauseGrouper>(clauses, query_.GetSelectSynonyms());

	result_table_ = EvaluateByGroup(clause_grouper);

	if (result_table_->IsEmpty()) {
		return false;
	}
	vector<string> select_synonyms = query_.GetSelectSynonyms();

	// If the result table from clauses does not contain any select synonyms,
	// we create a new empty result table
	if (!result_table_->ContainsSynonyms(select_synonyms)) {
		result_table_ = std::make_shared<WildcardTable>();
	}

	for (shared_ptr<Ref> ref : *select_tuple) {
		if (result_table_->ContainsSynonym(ref->GetName())) {
			continue;
		} 
		shared_ptr<ResWrapper> res_wrapper = data_retriever_.retrieve(ref);
		shared_ptr<Table> curr_result_table = std::make_shared<Table>(res_wrapper);

		result_table_ = result_table_->Join(curr_result_table);
	}

	return result_table_->GetNumOfRows() > 0;
}




shared_ptr<Table> QueryEvaluator::EvaluateGroup(vector<shared_ptr<Clause>> clauses) {
	shared_ptr<Table> table = std::make_shared<WildcardTable>();

	for (shared_ptr<Clause> clause : clauses) {
		shared_ptr<ResWrapper> res_wrapper = clause->GetMatch(data_retriever_);
		if (res_wrapper->GetResType() == ResType::kBool) {
			if (res_wrapper->IsValid()) {
				continue;
			}
			else {
				return std::make_shared<EmptyTable>();
			}	
		}

		shared_ptr<Table> result_table = std::make_shared<Table>(res_wrapper);

		table = table->Join(result_table);
		if (table->GetNumOfRows() == 0) {
			return table;
		}
	}
	return table;
}

std::shared_ptr<Table> QueryEvaluator::EvaluateByGroup(shared_ptr<ClauseGrouper> clause_grouper) {
	bool is_success = EvaluateNoSynGroup(clause_grouper->GetClauseGroupWoSyn());
	if (!is_success) {
		return std::make_shared<EmptyTable>();
	}
	is_success = EvaluateNoSelectSynGroups(clause_grouper->GetClauseGroupsWoSelectSyn());

	if (!is_success) {
		return std::make_shared<EmptyTable>();
	}

	shared_ptr<Table> table = EvaluateSelectSynGroups(clause_grouper->GetClauseGroupsWithSelectSyn());
	return table;
}


bool QueryEvaluator::EvaluateNoSynGroup(std::shared_ptr<ClauseGroup> group_wo_syn_) {
	for (shared_ptr<Clause> clause : group_wo_syn_->GetClauses()) {
		shared_ptr<ResWrapper> res_wrapper = clause->GetMatch(data_retriever_);
		if (res_wrapper->IsValid()) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

bool QueryEvaluator::EvaluateNoSelectSynGroup(std::shared_ptr<ClauseGroup> group_wo_select_syn_) {
	shared_ptr<Table> table = std::make_shared<WildcardTable>();

	for (shared_ptr<Clause> clause : group_wo_select_syn_->GetClauses()) {
		shared_ptr<ResWrapper> res_wrapper = clause->GetMatch(data_retriever_);

		if (res_wrapper->GetResType() == ResType::kBool) {
			if (res_wrapper->IsValid()) {
				continue;
			}
			else {
				return false;
			}
		}

		shared_ptr<Table> result_table = std::make_shared<Table>(res_wrapper);
		table = table->Join(result_table);
		if (table->GetNumOfRows() == 0) {
			return false;
		}
	}

	return true;
}

bool QueryEvaluator::EvaluateNoSelectSynGroups(std::vector<std::shared_ptr<ClauseGroup>> groups_wo_select_syn_) {
	for (std::shared_ptr<ClauseGroup> clause_group : groups_wo_select_syn_) {
		bool is_success = EvaluateNoSelectSynGroup(clause_group);
		if (!is_success) return false;
	}
	return true;
}



std::shared_ptr<Table> QueryEvaluator::EvaluateSelectSynGroup(std::shared_ptr<ClauseGroup> group_w_select_syn_) {
	shared_ptr<Table> table = std::make_shared<WildcardTable>();

	for (shared_ptr<Clause> clause : group_w_select_syn_->GetClauses()) {
		shared_ptr<ResWrapper> res_wrapper = clause->GetMatch(data_retriever_);
		if (res_wrapper->GetResType() == ResType::kBool) {
			if (res_wrapper->IsValid()) {
				continue;
			}
			else {
				return std::make_shared<EmptyTable>();
			}
		}

		shared_ptr<Table> result_table = std::make_shared<Table>(res_wrapper);
		table = table->Join(result_table);
		if (table->GetNumOfRows() == 0) {
			return table;
		}
	}
	return table;
}


std::shared_ptr<Table> QueryEvaluator::EvaluateSelectSynGroups(std::vector<std::shared_ptr<ClauseGroup>> groups_w_select_syn_) {
	shared_ptr<Table> table = std::make_shared<WildcardTable>();
	for (std::shared_ptr<ClauseGroup> clause_group : groups_w_select_syn_) {
		shared_ptr<Table> curr_res_table = EvaluateSelectSynGroup(clause_group);

		table = table->Join(curr_res_table);
		if (table->GetNumOfRows() == 0) {
			return table;
		}
	}
	return table;
}


vector<std::string> QueryEvaluator::ExtractResult() {
	vector<std::string> result;

	if (query_.IsBoolean()) {
		if (result_table_->IsEmpty()) {
			result.push_back("FALSE");
		}
		else {
			result.push_back("TRUE");
		}
		return result;
	}

	ResultExtractor result_extractor = ResultExtractor(result_table_, query_.GetSelectSynonyms());
	result = result_extractor.GetFormattedResult();

	return result;
}


	
