#pragma once

#include <string>
#include <unordered_map>
#include <tuple>

using std::string;

template<typename n_tuple>
class ResTable
{
protected:
    unordered_map<string, int> syn_to_col_;  // maps synonym name to tuple col index
    vector<n_tuple> rows_;

public:
    n_tuple Get(int index) { return rows_[index]; }

    string Get(int index, string syn);
};