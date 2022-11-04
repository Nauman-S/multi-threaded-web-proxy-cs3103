#include "QueryEvaluator.h"

#include <string>
#include <memory>

#include "Query.h"
#include "clause/relation/Rel.h"
#include "ResultExtractor.h"
#include "query_result/table/Table.h"
#include "query_result/table/TableFactory.h"
#include "optimization/clause_grouper/ClauseGrouper.h"
#include "optimization/clause_grouper/SimpleClauseGrouper.h"
#include "optimization/clause_grouper/OptimizedClauseGrouper.h"

using std::vector;
using std::shared_ptr;
using std::string;

QueryEvaluator::QueryEvaluator(Query query) {
    query_ = query;
    data_retriever_ = DataRetriever();
}

QueryEvaluator::QueryEvaluator(Query query, DataRetriever data_retriever) {
    query_ = query;
    data_retriever_ = data_retriever;
}

bool QueryEvaluator::Evaluate() {
    shared_ptr<vector<shared_ptr<Ref>>> select_tuple = query_.GetSelectTuple();

    std::vector<shared_ptr<Clause>> clauses = *query_.GetAllClauses();

    shared_ptr<ClauseGrouper> clause_grouper = std::make_shared<OptimizedClauseGrouper>(clauses, query_.GetSelectSynonyms());

    result_table_ = EvaluateByGroup(clause_grouper);

    if (result_table_->IsEmpty()) {
        return false;
    }
    vector<string> select_synonyms = query_.GetSelectSynonyms();

    // add select synonyms not in clauses to result table
    for (shared_ptr<Ref> ref : *select_tuple) {
        if (result_table_->HasSynonym(ref->GetName())) {
            continue;
        }
        shared_ptr<ResWrapper> res_wrapper = data_retriever_.retrieve(ref);
        shared_ptr<Table> curr_result_table = TableFactory::CreateTable(res_wrapper);
        result_table_ = result_table_->Join(curr_result_table);
    }

    return !result_table_->IsEmpty();
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
        if (!res_wrapper->IsValid()) {
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


bool QueryEvaluator::EvaluateNoSelectSynGroup(std::shared_ptr<ClauseGroup> group_wo_select_syn_) {
    shared_ptr<Table> table = std::make_shared<WildcardTable>();
    shared_ptr<ClauseGroup> sorted_clause_group = clause_sorter_.SortClausesInGroup(group_wo_select_syn_);

    for (shared_ptr<Clause> clause : sorted_clause_group->GetClauses()) {
        shared_ptr<ResWrapper> res_wrapper = clause->GetMatch(data_retriever_);

        shared_ptr<Table> result_table = TableFactory::CreateTable(res_wrapper);
        table = table->Join(result_table);
        if (table->IsEmpty()) {
            return false;
        }
    }

    return true;
}


std::shared_ptr<Table> QueryEvaluator::EvaluateSelectSynGroups(std::vector<std::shared_ptr<ClauseGroup>> groups_w_select_syn_) {
    shared_ptr<Table> table = std::make_shared<WildcardTable>();
    for (std::shared_ptr<ClauseGroup> clause_group : groups_w_select_syn_) {
        shared_ptr<Table> curr_res_table = EvaluateSelectSynGroup(clause_group);

        table = table->Join(curr_res_table);
        if (table->IsEmpty()) {
            return table;
        }
    }
    return table;
}

std::shared_ptr<Table> QueryEvaluator::EvaluateSelectSynGroup(std::shared_ptr<ClauseGroup> group_w_select_syn_) {
    shared_ptr<Table> table = std::make_shared<WildcardTable>();
    shared_ptr<ClauseGroup> sorted_clause_group = clause_sorter_.SortClausesInGroup(group_w_select_syn_);

    for (shared_ptr<Clause> clause : sorted_clause_group->GetClauses()) {
        shared_ptr<ResWrapper> res_wrapper = clause->GetMatch(data_retriever_);
        shared_ptr<Table> result_table = TableFactory::CreateTable(res_wrapper);
        table = table->Join(result_table);
        if (table->IsEmpty()) {
            return table;
        }
    }
    return table;
}


vector<std::string> QueryEvaluator::ExtractResult() {
    ResultExtractor result_extractor = ResultExtractor(result_table_, query_);
    vector<std::string> result = result_extractor.ExtractResult(data_retriever_);
    return result;
}
