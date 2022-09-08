#include "TableRes.h"

#include <assert.h>

#include "../../Utils/type/TypeDef.h"

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::tuple;
using std::shared_ptr;
using StrPair = std::pair<string, string>;


shared_ptr<vector<string>> TableRes::Columns()
{
    auto vec = std::shared_ptr<vector<string>>();
    for (auto& [syn, idx] : syn_to_col_) {
        vec->push_back(syn);
    }

    return vec;
}

shared_ptr<unordered_set<string>> TableRes::GetColumn(string syn_name) {
    auto iterator = syn_to_col_.find(syn_name);
    if (iterator == syn_to_col_.end()) {
        return nullptr;
    }
    int col_index = iterator->second;
    assert(col_index == 0 || col_index == 1);
    shared_ptr<unordered_set<string>> result_set = std::make_shared<unordered_set<string>>();
    
    if (col_index == 0) {
        for (StrPair pair : (*rows_ptr_)) {
            result_set->insert(pair.first);
        }
    }
    else if (col_index == 1) {
        for (StrPair pair : (*rows_ptr_)) {
            result_set->insert(pair.second);
        }
    }
    return result_set;

}