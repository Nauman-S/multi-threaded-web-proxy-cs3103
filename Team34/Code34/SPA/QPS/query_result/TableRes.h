#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <memory>
#include <utility>

#include "../../Utils/type/TypeDef.h"


class TableRes {
protected:
    std::unordered_map<std::string, int> syn_to_col_;  // maps synonym name to tuple col index
    std::shared_ptr<std::vector<StrPair>> rows_ptr_;

public:
    TableRes(std::unordered_map<std::string, int> s2c, std::shared_ptr<std::vector<StrPair>> rows) 
        : syn_to_col_(s2c), rows_ptr_(rows) {}

    bool Contains(std::string key);

    std::unordered_map<std::string, int> GetSynMap() { return syn_to_col_; }

    std::shared_ptr<std::vector<std::string>> Columns();

    std::shared_ptr<std::unordered_set<std::string>> ColumnsSet();

    std::shared_ptr<std::unordered_set<std::string>> GetColumn(std::string syn_name);

    int GetColumnIndex(std::string syn_name) { return syn_to_col_[syn_name]; }

    StrPair GetRow(int index) { return (*rows_ptr_)[index]; }

    std::shared_ptr<const std::vector<StrPair>> GetRows();

    bool IsEmpty() { return rows_ptr_->empty(); }
};

inline bool TableRes::Contains(std::string key) {
    return syn_to_col_.find(key) != syn_to_col_.end();
}
