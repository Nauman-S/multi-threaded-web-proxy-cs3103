#pragma once

#include "query_result/QueryResult.h"
#include "reference/Ref.h"

using std::shared_ptr;
using std::unordered_map;
using std::vector;

class ResultExtractor {
private:
	shared_ptr < std::vector<Ref>> select_tuple_;
	shared_ptr<QueryResult> query_result_;

	string GetSingleSynResult();


public:
	ResultExtractor(shared_ptr<QueryResult> query_result, shared_ptr < std::vector<Ref>> select_tuple) 
		: query_result_{ query_result }, select_tuple_{select_tuple} {};

	string GetFormattedResult();

	string GetMultiSynResult();

	shared_ptr<unordered_set<string>> CombineResult(shared_ptr<unordered_set<string>> result_set1, shared_ptr<unordered_set<string>> result_set2);

	string FormatResult(shared_ptr<unordered_set<string>> result_set, RefType ref_type);
};

