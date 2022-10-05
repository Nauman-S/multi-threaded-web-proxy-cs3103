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
	//std::shared_ptr<std::vector<std::shared_ptr<Ref>>> select_tuple_;
	std::shared_ptr<QueryResult> query_result_;
	std::shared_ptr<Table> result_table_;
	std::vector<std::string> select_synonyms_;

public:
	//ResultExtractor(std::shared_ptr<QueryResult> query_result, std/*::shared_ptr<std::vector<std::shared_ptr<Ref>>> select_tuple)
	//	: query_result_{ query_result }, select_tuple_{select_tuple} {};*/

	ResultExtractor(std::shared_ptr<Table> result_table, std::vector<std::string> select_synonyms)
		: result_table_{ result_table }, select_synonyms_{ select_synonyms } {};


	std::vector<std::string> GetFormattedResult();

	std::vector<std::string> GetSingleSynResult();

	std::vector<std::string> GetMultiSynResult();

	std::shared_ptr<std::unordered_set<std::string>> CombineResult(std::shared_ptr<std::unordered_set<std::string>> result_set1, std::shared_ptr<std::unordered_set<std::string>> result_set2);

	std::vector<std::string> FormatResult(std::shared_ptr<std::unordered_set<std::string>> result_set);

};

