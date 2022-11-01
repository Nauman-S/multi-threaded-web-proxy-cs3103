#include "ResultExtractor.h"

#include <assert.h>

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

#include "../Utils/type/RefType.h"

using std::string;
using std::unordered_set;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

vector<std::string> ResultExtractor::ExtractResult(DataRetriever& data_retriever) {
	vector<std::string> results;

    if (is_boolean_result) {
        if (result_table_->IsEmpty()) {
            results.push_back("FALSE");
        } else {
            results.push_back("TRUE");
        }
        return results;
    }

    if (result_table_->IsEmpty()) {
        return results;
    }

	return GetFormattedResult(data_retriever);
}

vector<std::string> ResultExtractor::GetFormattedResult(DataRetriever& data_retriever) {
    
    
    shared_ptr<vector<vector<string>>> result_rows = result_table_->ExtractSynonyms(select_synonyms_);

    for (size_t pos = 0; pos < tuple_->size(); ++pos) {
        shared_ptr<Ref> ref = tuple_->at(pos);
        if (ref->IsAttrTypeDefault()) {
            continue;
        }

        // replace the value with attribute value 
        for (vector<string>& row : *result_rows) {
            string attr_value = ref->GetAttrValue(data_retriever, row.at(pos));
            row[pos] = attr_value;
        }
    }

    shared_ptr<std::unordered_set<std::string>> result_set = std::make_shared< std::unordered_set<std::string>>();

    string delimiter = " ";
    for (auto& row : *result_rows) {
        string row_result;
        for (string& cell : row) {
            row_result += (cell + delimiter);
        }

        // remove the extra trailing space
        row_result.pop_back();
        result_set->insert(row_result);
    }

    std::vector<string> result_vector(result_set->begin(), result_set->end());
    return result_vector;
}
