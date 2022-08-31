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
using TwoTuple = std::pair<string, string>;
using ThreeTuple = std::tuple<string, string, string>;

template<typename n_tuple>
class TableRes
{
protected:
    unordered_map<string, int> syn_to_col_;  // maps synonym name to tuple col index
    vector<n_tuple> rows_;

public:
    TableRes(unordered_map<string, int> s2c, vector<n_tuple> rows) : syn_to_col_(s2c), rows_(rows) {};

    bool Contains(string key);

    vector<string>& Columns();

    n_tuple GetRow(int index) { return rows_[index]; }

    string GetValue(int index, string syn);
};

template<typename n_tuple>
inline bool TableRes<n_tuple>::Contains(string key)
{
    return syn_to_col_.find(key) != syn_to_col_.end();
}

template<typename n_tuple>
inline vector<string>& TableRes<n_tuple>::Columns()
{
    auto vec = std::shared_ptr<vector<string>>();
    for (auto& [col, idx] : syn_to_col_) {
        vec.push_back(col);
    }

    return vec;
}

template<typename n_tuple>
inline string TableRes<n_tuple>::GetValue(int index, string syn)
{
    if (auto col = syn_to_col_[syn]; col != syn_to_col_.end()) {
        return std::get<col>(rows_[index]);
    }
    else {
        return "";
    }
    
}
