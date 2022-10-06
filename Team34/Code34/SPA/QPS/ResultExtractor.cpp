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
	assert(select_synonyms_.size() > 0 && "Size of tuple must be greater than 0");

	if (select_synonyms_.size() == 1) {
		return GetSingleSynResult();
	}
	else {
		return GetMultiSynResult();
	}
}

vector<std::string> ResultExtractor::GetSingleSynResult() {
	string name = select_synonyms_.at(0);
	shared_ptr<unordered_set<string>> result_set = result_table_->GetDomainBySynonym(name);
	return FormatResult(result_set);

}

vector<std::string> ResultExtractor::GetMultiSynResult() {
	shared_ptr<unordered_set<string>> result_set = result_table_->GetDomainBySynonyms(select_synonyms_);

	return FormatResult(result_set);
}

//shared_ptr<unordered_set<string>> ResultExtractor::CombineResult(shared_ptr<unordered_set<string>> result_set1, shared_ptr<unordered_set<string>> result_set2) {
//	shared_ptr<unordered_set<string>> combined_result = std::make_shared<unordered_set<string>>();
//
//	for (auto itr = result_set1->begin(); itr != result_set1->end(); itr++) {
//		if (result_set2->count(*itr)) {
//			combined_result->insert(*itr);
//		}
//	}
//	return combined_result;
//}

vector<std::string> ResultExtractor::FormatResult(shared_ptr<unordered_set<string>> result_set) {
	std::vector<string> result_vector(result_set->begin(), result_set->end());

	std::sort(result_vector.begin(), result_vector.end());

	return result_vector;
}

