#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <memory>

#include "query_result/QueryResult.h"
#include "query_result/Table.h"
#include "reference/Ref.h"

class ResultExtractor {
private:
	std::shared_ptr<QueryResult> query_result_;
	std::shared_ptr<Table> result_table_;
	std::vector<std::string> select_synonyms_;

public:
	ResultExtractor(std::shared_ptr<Table> result_table, std::vector<std::string> select_synonyms)
		: result_table_{ result_table }, select_synonyms_{ select_synonyms } {};

	std::vector<std::string> GetFormattedResult();

	std::vector<std::string> GetSingleSynResult();

	std::vector<std::string> GetMultiSynResult();

	std::vector<std::string> FormatResult(std::shared_ptr<std::unordered_set<std::string>> result_set);

};

