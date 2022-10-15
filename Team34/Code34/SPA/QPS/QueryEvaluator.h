#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Clause.h"
#include "DataRetriever.h"
#include "Query.h"
#include "clause_grouper/ClauseGrouper.h"
#include "pattern/Pattern.h"
#include "query_result/QueryResult.h"
#include "query_result/Table.h"
#include "reference/Ref.h"
#include "relation/Rel.h"

class QueryEvaluator {
protected:
    Query query_;
    shared_ptr<Table> result_table_;
    std::vector<Clause> clauses_;
    DataRetriever data_retriever_;

    std::shared_ptr<Table> EvaluateByGroup(
        shared_ptr<ClauseGrouper> clause_grouper);
    bool EvaluateNoSynGroup(std::shared_ptr<ClauseGroup> group_wo_syn_);

    bool EvaluateNoSelectSynGroup(
        std::shared_ptr<ClauseGroup> group_wo_select_syn_);
    bool EvaluateNoSelectSynGroups(
        std::vector<std::shared_ptr<ClauseGroup>> groups_wo_select_syn_);

    std::shared_ptr<Table> EvaluateSelectSynGroup(
        std::shared_ptr<ClauseGroup> group_w_select_syn_);
    std::shared_ptr<Table> EvaluateSelectSynGroups(
        std::vector<std::shared_ptr<ClauseGroup>> groups_w_select_syn_);

public:
    QueryEvaluator(Query query);
    QueryEvaluator(Query query, DataRetriever data_retriever);
    bool Evaluate();

    std::vector<std::string> ExtractResult();
};
