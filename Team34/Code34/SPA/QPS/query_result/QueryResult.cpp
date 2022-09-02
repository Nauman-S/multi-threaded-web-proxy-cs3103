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
	else {
		// TODO: change to assert
		return false;
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
		set_results_.insert({ sym, set_res });
		return true;
	} 

	set_results_.at(sym)->Merge(set_res);
	return true;

}

bool QueryResult::MergeTableResult(ResWrapper& res_wrapper) {
	table_results.push_back(res_wrapper.GetTable());
	return true;
}