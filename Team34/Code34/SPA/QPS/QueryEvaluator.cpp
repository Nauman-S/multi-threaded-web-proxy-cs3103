#include "QueryEvaluator.h"

#include <memory.h>

#include "Query.h"
#include "relation/Rel.h"
#include "ResultExtractor.h"
#include "query_result/Table.h"
#include "query_result/EmptyTable.h"

using std::vector;
using std::shared_ptr;


QueryEvaluator::QueryEvaluator(Query query) {
	query_ = query;
	query_result_ = QueryResult();
	data_retriever_ = DataRetriever();
};


bool QueryEvaluator::Evaluate() {
	shared_ptr<vector<shared_ptr<Ref>>> select_tuple = query_.GetSelectTuple();
	//for (shared_ptr<Ref> ref : *select_tuple) {
	//	//shared_ptr<ResWrapper> res_wrapper = data_retriever_.retrieve(std::make_shared<Ref>(ref));
	//	shared_ptr<ResWrapper> res_wrapper = data_retriever_.retrieve(ref);
	//	bool success = query_result_.MergeResult(res_wrapper);
	//	if (!success) {
	//		return false;
	//	}
	//}

	std::vector<shared_ptr<Clause>> clauses;

	shared_ptr<std::vector<shared_ptr<Rel>>> relations = query_.GetRelations();
	shared_ptr<std::vector<shared_ptr<Pattern>>> patterns = query_.GetPatterns();
	shared_ptr<std::vector<shared_ptr<With>>> with_clauses = query_.GetWithClauses();

	clauses.insert(clauses.end(), relations->begin(), relations->end());
	clauses.insert(clauses.end(), patterns->begin(), patterns->end());
	clauses.insert(clauses.end(), with_clauses->begin(), with_clauses->end());


	result_table_ = EvaluateGroup(clauses);
	if (result_table_->IsEmpty()) {
		return false;
	}
	vector<string> select_synonyms = query_.GetSelectSynonyms();

	// If the result table from clauses does not contain any select synonyms,
	// we create a new empty result table
	if (!result_table_->ContainsSynonyms(select_synonyms)) {
		result_table_ = std::make_shared<Table>();
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
	shared_ptr<Table> table = std::make_shared<Table>();

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

vector<std::string> QueryEvaluator::ExtractResult() {
	//ResultExtractor result_extractor = ResultExtractor(std::make_shared<QueryResult>(query_result_), query_.GetSelectTuple());

	ResultExtractor result_extractor = ResultExtractor(result_table_, query_.GetSelectTuple());


	return result_extractor.GetFormattedResult();
}


	
