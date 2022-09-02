#pragma once

#include <string>

#include "SetRes.h"
#include "TableRes.h"
#include "ResWrapper.h"

class QueryResult {
protected:
	std::unordered_map<string, std::shared_ptr<SetRes>> set_results_;
	std::vector<std::shared_ptr<TableRes>> table_results;

	bool MergeSetResult(ResWrapper& res_wrapper);
	bool MergeTableResult(ResWrapper& res_wrapper);

public:
	bool MergeResult(ResWrapper& res_wrapper);


};

