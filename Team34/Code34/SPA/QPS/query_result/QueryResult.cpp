#include "QueryResult.h"

#include "ResType.h"

bool QueryResult::MergeResult(ResWrapper& res_wrapper) {
	ResType type = res_wrapper.GetResType();
	if (type == ResType::kBool) {
		return res_wrapper.IsValid();
	} 

	if (type == ResType::kSet) {
		return MergeSetResult(res_wrapper);
	}
	else if (type == ResType::kTable) {
		return MergeTableResult(res_wrapper);
	}
}


bool QueryResult::MergeSetResult(ResWrapper& res_wrapper) {
	std::shared_ptr<SetRes> set_res = res_wrapper.GetSet();


	string sym = set_res->GetSyn();
	unordered_set<string>& res_set = set_res->GetDomain();

	// check whether the domain is empty
	if (res_set.size() == 0) {
		return false;
	}

	if (set_results_.count(sym) == 0) {
		set_results_.insert({ sym, std::make_shared<unordered_set<string>>(res_set) });
		return true;
	} 

	unordered_set<string> merged_result;
	for (const string& s : res_set) {
		if (set_results_.count(s)) {
			merged_result.insert(s);
		}
	}

	if (merged_result.size() == 0) {
		return false;
	}
	else {
		set_results_.insert({ sym, std::make_shared<unordered_set<string>>(merged_result) });
		return true;
	}
}

bool QueryResult::MergeTableResult(ResWrapper& res_wrapper) {

}