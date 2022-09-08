#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <memory>

#include "query_result/QueryResult.h"
#include "reference/Ref.h"


class ResultExtractor {
private:
	std::shared_ptr<std::vector<std::shared_ptr<Ref>>> select_tuple_;
	std::shared_ptr<QueryResult> query_result_;

	std::string GetSingleSynResult();


public:
	ResultExtractor(std::shared_ptr<QueryResult> query_result, std::shared_ptr<std::vector<std::shared_ptr<Ref>>> select_tuple)
		: query_result_{ query_result }, select_tuple_{select_tuple} {};

	std::string GetFormattedResult();

	std::string GetMultiSynResult();

	std::shared_ptr<std::unordered_set<std::string>> CombineResult(std::shared_ptr<std::unordered_set<std::string>> result_set1, std::shared_ptr<std::unordered_set<std::string>> result_set2);

	std::string FormatResult(std::shared_ptr<std::unordered_set<std::string>> result_set, RefType ref_type);
};

