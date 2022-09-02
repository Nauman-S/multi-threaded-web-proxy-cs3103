#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "reference/Ref.h"
#include "relation/Rel.h"
#include "pattern/Pattern.h"
#include "Clause.h"
#include "DataRetriever.h"
#include "Query.h"


class QueryEvaluator
{
protected:
	Query query_;
	//std::unordered_map<Ref, std::vector<std::string>> syn_domains_;

	std::vector<Clause> clauses_;
	DataRetriever data_retriever_;


public:
	QueryEvaluator(Query query);

	bool evaluate();
};

