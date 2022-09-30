#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "reference/Ref.h"
#include "relation/Rel.h"
#include "pattern/Pattern.h"
#include "query_result/QueryResult.h"
#include "query_result/Table.h"
#include "Clause.h"
#include "DataRetriever.h"
#include "Query.h"



class QueryEvaluator
{
protected:
	Query query_;
	//std::unordered_map<Ref, std::vector<std::string>> syn_domains_;
	QueryResult query_result_;
	shared_ptr<Table> result_table_;
	std::vector<Clause> clauses_;
	DataRetriever data_retriever_;

	std::shared_ptr<Table> EvaluateGroup(std::vector<std::shared_ptr<Clause>>);

public:
	QueryEvaluator(Query query);

	bool Evaluate();

	std::vector<std::string> ExtractResult();

	std::vector<std::string> GetSelectSynonyms();
};

