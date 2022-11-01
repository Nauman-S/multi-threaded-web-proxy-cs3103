#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <memory>

#include "query_result/table/Table.h"
#include "reference/Ref.h"
#include "DataRetriever.h"
#include "Query.h"

class ResultExtractor {
private:
	std::shared_ptr<Table> result_table_;
	std::vector<std::string> select_synonyms_;
	std::shared_ptr<std::vector<std::shared_ptr<Ref>>> tuple_;
	bool is_boolean_result;

public:
	ResultExtractor(std::shared_ptr<Table> result_table, Query query)
		: result_table_{ result_table } {
		select_synonyms_ = query.GetSelectSynonyms();
		tuple_ = query.GetSelectTuple();
		is_boolean_result = query.IsBoolean();
	};


	std::vector<std::string> ExtractResult(DataRetriever&);

	std::vector<std::string> GetFormattedResult(DataRetriever&);

};
