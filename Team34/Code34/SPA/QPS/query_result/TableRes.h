#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <memory>

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::tuple;
using std::shared_ptr;
using StrPair = std::pair<string, string>;

class TableRes {
protected:
    unordered_map<string, int> syn_to_col_;  // maps synonym name to tuple col index
    vector<StrPair> rows_;

public:
    TableRes(unordered_map<string, int> s2c, vector<StrPair> rows) : syn_to_col_(s2c), rows_(rows) {};

    bool Contains(string key);

    shared_ptr<vector<string>> Columns();

    shared_ptr<unordered_set<string>> GetColumn(string syn_name);

    StrPair GetRow(int index) { return rows_[index]; }

    //string GetValue(int index, string syn);
};

inline bool TableRes::Contains(string key)
{
    return syn_to_col_.find(key) != syn_to_col_.end();
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
