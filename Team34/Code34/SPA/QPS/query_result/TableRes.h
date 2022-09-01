#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <memory>

using std::string;
using std::unordered_map;
using std::vector;
using std::tuple;
using Pair = std::pair<string, string>;

class TableRes
{
protected:
    unordered_map<string, int> syn_to_col_;  // maps synonym name to tuple col index
    vector<Pair> rows_;

public:
    TableRes(unordered_map<string, int> s2c, vector<Pair> rows) : syn_to_col_(s2c), rows_(rows) {};

    bool Contains(string key);

    std::shared_ptr<vector<string>> Columns();

    Pair GetRow(int index) { return rows_[index]; }

    string GetValue(int index, string syn);
};

inline bool TableRes::Contains(string key)
{
    return syn_to_col_.find(key) != syn_to_col_.end();
}

inline std::shared_ptr<vector<string>> TableRes::Columns()
{
    auto vec = std::shared_ptr<vector<string>>();
    for (auto& [col, idx] : syn_to_col_) {
        vec->push_back(col);
    }

    return vec;
}

//inline string TableRes::GetValue(int index, string syn)
//{
//    if (auto col = syn_to_col_.find(syn); col != syn_to_col_.end()) {
//        return rows_[index].first();
//    }
//    else {
//        return "";
//    }
//    
//}
