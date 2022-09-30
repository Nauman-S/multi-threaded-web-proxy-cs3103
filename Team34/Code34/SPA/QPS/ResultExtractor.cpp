#include "ResultExtractor.h"

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>
#include <assert.h>

#include "../Utils/type/RefType.h"

using std::string;
using std::unordered_set;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

vector<std::string> ResultExtractor::GetFormattedResult() {

	// assert the number of syns in tuple > 0;
	assert(select_tuple_->size() > 0 && "Size of tuple must be greater than 0");

	if (select_tuple_->size() == 1) {
		return GetSingleSynResult();
	}
	else {
		return GetMultiSynResult();
	}
}

vector<std::string> ResultExtractor::GetSingleSynResult() {
	shared_ptr<Ref> ref = select_tuple_->at(0);

	//// Get the domain in set results;
	//unordered_map<string, shared_ptr<SetRes>> set_results = query_result_->GetSetResults();
	//
	//auto iterator = set_results.find(ref->GetName());
	//assert(iterator != set_results.end() && "Result does not contain the synonym");

	//shared_ptr<unordered_set<string>> result_set = iterator->second->GetDomain();

	// Get the domain in table results;

	//vector<shared_ptr<TableRes>> table_results = query_result_->GetTableResults();
	//for (shared_ptr<TableRes> table_result : table_results) {
	//	shared_ptr<unordered_set<string>> domain_from_table = table_result->GetColumn(ref->GetName());
	//	if (domain_from_table == nullptr) {
	//		continue;
	//	}
	//	result_set = CombineResult(result_set, domain_from_table);
	//	
	//}
	shared_ptr<unordered_set<string>> result_set = result_table_->GetDomainBySynonym(ref->GetName());
	return FormatResult(result_set, ref->GetRefType());

}

vector<std::string> ResultExtractor::GetMultiSynResult() {
	return std::vector<string>();
}

shared_ptr<unordered_set<string>> ResultExtractor::CombineResult(shared_ptr<unordered_set<string>> result_set1, shared_ptr<unordered_set<string>> result_set2) {
	shared_ptr<unordered_set<string>> combined_result = std::make_shared<unordered_set<string>>();

	for (auto itr = result_set1->begin(); itr != result_set1->end(); itr++) {
		if (result_set2->count(*itr)) {
			combined_result->insert(*itr);
		}
	}

	return combined_result;
}

vector<std::string> ResultExtractor::FormatResult(shared_ptr<unordered_set<string>> result_set, RefType ref_type) {
	std::vector<string> result_vector(result_set->begin(), result_set->end());

	std::sort(result_vector.begin(), result_vector.end());

	return result_vector;
}

