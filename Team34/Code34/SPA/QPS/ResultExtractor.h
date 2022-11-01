#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <memory>

#include "query_result/table/Table.h"
#include "reference/Ref.h"
#include "DataRetriever.h"

class ResultExtractor {
private:
	std::shared_ptr<Table> result_table_;
	std::vector<std::string> select_synonyms_;
	std::shared_ptr<std::vector<std::shared_ptr<Ref>>> tuple_;


public:
	ResultExtractor(std::shared_ptr<Table> result_table, std::vector<std::string> select_synonyms,
		std::shared_ptr<std::vector<std::shared_ptr<Ref>>> tuple)
		: result_table_{ result_table }, select_synonyms_{ select_synonyms }, tuple_{ tuple } {};

	std::vector<std::string> ExtractResult(DataRetriever&);

	std::vector<std::string> GetFormattedResult(DataRetriever&);

};

