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

vector<std::string> ResultExtractor::GetFormattedResult(DataRetriever& data_retriever) {
	vector<std::string> results;
	if (result_table_->IsEmpty()) {
		return results;
	}
	return GetMultiSynResult(data_retriever);
}

vector<std::string> ResultExtractor::GetSingleSynResult(DataRetriever& data_retriever) {
	string name = select_synonyms_.at(0);
	shared_ptr<unordered_set<string>> result_set = result_table_->GetDomainBySynonym(name);
	return FormatResult(result_set);
}

vector<std::string> ResultExtractor::GetMultiSynResult(DataRetriever& data_retriever) {
	//shared_ptr<unordered_set<string>> result_set = result_table_->GetDomainBySynonyms(select_synonyms_);

	shared_ptr<vector<vector<string>>> result_rows = result_table_->ExtractSynonyms(select_synonyms_);
	
	for (unsigned pos = 0; pos < tuple_->size(); ++pos) {
		shared_ptr<Ref> ref = tuple_->at(pos);
		if (ref->IsAttrTypeDefault()) {
			continue;
		}

		for (vector<string>& row : *result_rows) {
			string attr_value = ref->GetAttrValue(data_retriever, row.at(pos));
			row[pos] = attr_value;
		}
	}

	shared_ptr <std::unordered_set<std::string>> result_set = std::make_shared< std::unordered_set<std::string>>();
	for (auto& row : *result_rows) {
		string row_result = "";
		for (string& cell : row) {
			
			row_result += (cell + " ");
		}

		// remove the extra trailing space
		row_result.pop_back();
		result_set->insert(row_result);
	}

	
	return FormatResult(result_set);
}

vector<std::string> ResultExtractor::FormatResult(shared_ptr<unordered_set<string>> result_set) {
	std::vector<string> result_vector(result_set->begin(), result_set->end());
	std::sort(result_vector.begin(), result_vector.end());
	return result_vector;
}

