#include "ResultExtractor.h"

#include <assert.h>
#include <algorithm>
#include "../Utils/type/RefType.h"

string ResultExtractor::GetFormattedResult() {

	// assert the number of syns in tuple > 0;
	assert(select_tuple_->size() > 0 && "Size of tuple must be greater than 0");

	if (select_tuple_->size() == 1) {
		return GetSingleSynResult();
	}
	else {
		return GetMultiSynResult();
	}
}

string ResultExtractor::GetSingleSynResult() {
	shared_ptr<Ref> ref = select_tuple_->at(0);

	// Get the domain in set results;
	shared_ptr<unordered_map<string, shared_ptr<SetRes>>> set_results = query_result_->GetSetResults();
	
	auto iterator = set_results->find(ref->GetName());
	assert(iterator != set_results->end() && "Result does not contain the synonym");

	shared_ptr<unordered_set<string>> result_set = iterator->second->GetDomain();

	// Get the domain in table results;

	shared_ptr<vector<shared_ptr<TableRes>>> table_results = query_result_->GetTableResults();
	for (shared_ptr<TableRes> table_result : *table_results) {
		shared_ptr<unordered_set<string>> domain_from_table = table_result->GetColumn(ref->GetName());
		if (domain_from_table == nullptr) {
			continue;
		}
		result_set = CombineResult(result_set, domain_from_table);
		
	}
	return FormatResult(result_set, ref->GetRefType());

}

string ResultExtractor::GetMultiSynResult() {
	return "GetMultiSynResult() is Not Implemented Yet";
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

string ResultExtractor::FormatResult(shared_ptr<unordered_set<string>> result_set, RefType ref_type) {
	std::vector<string> result_vector(result_set->begin(), result_set->end());

	std::sort(result_vector.begin(), result_vector.end());

	string final_result = "";
	for (string value : result_vector) {
		final_result += (value + " ");
	}
	return final_result;
}

