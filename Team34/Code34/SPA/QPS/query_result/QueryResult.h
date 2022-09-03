#pragma once

#include <string>

#include "SetRes.h"
#include "TableRes.h"
#include "ResWrapper.h"

using std::shared_ptr;
using std::unordered_map;
using std::vector;

class QueryResult {
protected:
	unordered_map<string, shared_ptr<SetRes>> set_results_;
	vector<shared_ptr<TableRes>> table_results_;

	bool MergeSetResult(ResWrapper& res_wrapper);
	bool MergeTableResult(ResWrapper& res_wrapper);

public:
	bool MergeResult(ResWrapper& res_wrapper);
	
	shared_ptr<unordered_map<string, shared_ptr<SetRes>>> GetSetResults() {
		return shared_ptr < unordered_map<string, shared_ptr<SetRes>>>(&set_results_);
	}

	shared_ptr<vector<shared_ptr<TableRes>>> GetTableResults() {
		return shared_ptr<vector<shared_ptr<TableRes>>>(&table_results_);
	}
};

