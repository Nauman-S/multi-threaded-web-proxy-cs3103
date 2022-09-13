#include "SpaAlgo.h"

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <sstream>
#include <cassert>

#include "../type/TypeDef.h"

using std::string;
using std::unordered_set;
using std::unordered_map;
using std::vector;
using std::stack;
using std::pair;
using std::shared_ptr;
using std::make_shared;

// Init static member
unordered_map<char, int> SpaAlgo::precedence_ = {
	{'+', 1},
	{'-', 1},
	{'*', 2},
	{'/', 2},
	{'%', 2},
};

string SpaAlgo::InfixToPostfix(string infix)
{
	stack<char> stk;
	string postfix = "";
	for (char& iter : infix) {
		if (iter == ' ') {
			continue;
		}
		else if (iter == '(') {
			stk.push(iter);
		}
		else if (iter == ')') {
			assert(!stk.empty());
			while (!stk.empty() && stk.top() != '(') {
				postfix += stk.top();
				stk.pop();
			}
			stk.pop();  // discard the '('
		}
		else if (auto p = SpaAlgo::precedence_.find(iter); p != SpaAlgo::precedence_.end()) {
			while (!stk.empty() && stk.top() != '(' && SpaAlgo::precedence_[stk.top()] >= p->second) {
				// assume all operators are left-associative
				postfix += stk.top();
				stk.pop();
			}
			stk.push(iter);
		}
		else {
			// is not an operator
			postfix += iter;
		}
	}

	while (!stk.empty()) {
		postfix += stk.top();
		stk.pop();
	}
	return postfix;
}

std::shared_ptr<SetRes> SpaAlgo::HashJoinSets(std::shared_ptr<SetRes> set_res_1, std::shared_ptr<SetRes> set_res_2)
{
	assert(set_res_1->GetSyn() == set_res_2->GetSyn());

	auto syn = set_res_1->GetSyn();
	auto set1 = set_res_1->GetDomain();
	auto set2 = set_res_2->GetDomain();

	shared_ptr<unordered_set<string>> intersect;
	std::set_intersection(set1->begin(), set1->end(), set2->begin(), set2->end(), std::inserter(*intersect, intersect->begin()));
	
	return make_shared<SetRes>(syn, intersect);
}

pair<shared_ptr<SetRes>, shared_ptr<TableRes>> SpaAlgo::HashJoinSetWithTable(std::shared_ptr<SetRes> set_res, std::shared_ptr<TableRes> table_res)
{
	string syn = set_res->GetSyn();
	assert(table_res->Contains(syn));

	auto set = set_res->GetDomain();
	shared_ptr<const vector<StrPair>> table = table_res->GetRows();
	int col_index = table_res->GetColumnIndex(syn);

	shared_ptr<unordered_set<string>> joined_set;
	shared_ptr<vector<StrPair>> joined_table;
	string join_val;
	for (auto iter=table->begin(); iter != table->end(); ++iter) {
		if (col_index == 0) {
			join_val = iter->first;
		}
		else {
			join_val = iter->second;
		}
		
		if (set->find(join_val) != set->end()) {
			joined_set->insert(join_val);
			joined_table->push_back(*iter);
		}
	}

	shared_ptr<SetRes> set_res = make_shared<SetRes>(syn, joined_set);
	shared_ptr<TableRes> table_res = make_shared<TableRes>(table_res->GetSynMap(), joined_table);
	return pair<shared_ptr<SetRes>, shared_ptr<TableRes>>(set_res, table_res);
}
