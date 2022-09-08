#pragma once

#include <string>

#include "SetRes.h"
#include "TableRes.h"
#include "ResWrapper.h"


class QueryResult {
protected:
	std::unordered_map<std::string, std::shared_ptr<SetRes>> set_results_;
	std::vector<std::shared_ptr<TableRes>> table_results_;

	bool MergeSetResult(ResWrapper& res_wrapper);
	bool MergeTableResult(ResWrapper& res_wrapper);

public:
	bool MergeResult(ResWrapper& res_wrapper);
	
	/*shared_ptr<unordered_map<string, shared_ptr<SetRes>>> GetSetResults() {
		return shared_ptr < unordered_map<string, shared_ptr<SetRes>>>(&set_results_);
	}*/

	std::unordered_map<std::string, std::shared_ptr<SetRes>> GetSetResults() {
		return set_results_;
	}

	//shared_ptr<vector<shared_ptr<TableRes>>> GetTableResults() {
	//	return shared_ptr<vector<shared_ptr<TableRes>>>(&table_results_);
	//}
	std::vector<std::shared_ptr<TableRes>> GetTableResults() {
		return table_results_;
	}
};

