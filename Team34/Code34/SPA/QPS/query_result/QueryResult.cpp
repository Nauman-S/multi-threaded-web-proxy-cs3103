#include "QueryResult.h"

#include <assert.h>

#include "ResType.h"
#include "../../Utils/algo/SpaAlgo.h"

using std::shared_ptr;
using std::unordered_map;
using std::vector;
using std::string;
using std::unordered_set;

bool QueryResult::MergeSetResult(shared_ptr<SetRes> other_set)
{
	string sym = other_set->GetSyn();
	shared_ptr<unordered_set<string>> res_domain = other_set->GetDomain();

	// check whether the domain is empty
	assert(res_domain != nullptr && "The result domain cannot be a nullptr");

	if (res_domain->size() == 0) {
		return false;
	}


	if (set_results_.count(sym) == 0) {
		set_results_.insert({ sym, other_set });
		return true;
	}

	set_results_.at(sym)->Merge(other_set);
	return true;
}

bool QueryResult::MergeTableResult(shared_ptr<TableRes> other_table)
{
	table_results_.push_back(other_table);
	return true;
}

bool QueryResult::MergeResult(shared_ptr<ResWrapper> res_wrapper) {
	ResType type = res_wrapper->GetResType();
	if (type == ResType::kBool) {
		return res_wrapper->IsValid();
	} 

	if (type == ResType::kSet) {
		shared_ptr<SetRes> set_res = res_wrapper->GetSet();
		return MergeSetResult(set_res);
	}
	else if (type == ResType::kTable) {
		shared_ptr<TableRes> table_res = res_wrapper->GetTable();
		return MergeTableResult(table_res);
	}
	else {
		// TODO: change to assert
		return false;
	}
	
}


//bool QueryResult::MergeSetResult(ResWrapper& res_wrapper) {
//	std::shared_ptr<SetRes> set_res = res_wrapper.GetSet();
//
//
//	string sym = set_res->GetSyn();
//	shared_ptr<unordered_set<string>> res_domain = set_res->GetDomain();
//
//	// check whether the domain is empty
//	assert(res_domain != nullptr && "The result domain cannot be a nullptr");
//
//	if (res_domain->size() == 0) {
//		return false;
//	}
//
//	
//	if (set_results_.count(sym) == 0) {
//		set_results_.insert({ sym, set_res });
//		return true;
//	} 
//
//	set_results_.at(sym)->Merge(set_res);
//	return true;
//
//}
//
//bool QueryResult::MergeTableResult(ResWrapper& res_wrapper) {
//	table_results_.push_back(res_wrapper.GetTable());
//	return true;
//}