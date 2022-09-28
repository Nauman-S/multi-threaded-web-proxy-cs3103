#include "SpaAlgo.h"

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <iostream>
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
using std::tuple;
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

unordered_map<string, int> SpaAlgo::precedence2_ = {
	{"+", 1},
	{"-", 1},
	{"*", 2},
	{"/", 2},
	{"%", 2},
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

string SpaAlgo::InfixToPostfix2(string& infix)
{
	stack<string> stk;
	string postfix = "";
	for (string& token : *Split(infix, ' ')) {
		if (token == "(") {
			stk.push(token);
		}
		else if (token == ")") {
			assert(!stk.empty());
			while (!stk.empty() && stk.top() != "(") {
				postfix += (stk.top() + " ");
				stk.pop();
			}
			stk.pop();  // discard the "("
		}
		else if (auto p = SpaAlgo::precedence2_.find(token); p != SpaAlgo::precedence2_.end()) {
			while (!stk.empty() && stk.top() != "(" && SpaAlgo::precedence2_[stk.top()] >= p->second) {
				// assume all operators are left-associative
				postfix += (stk.top() + " ");
				stk.pop();
			}
			stk.push(token);
		}
		else {
			// is not an operator
			postfix += (token + " ");
		}
	}

	while (!stk.empty()) {
		postfix += (stk.top() + " ");
		stk.pop();
	}
	return postfix;
}

std::shared_ptr<std::vector<std::string>> SpaAlgo::Split(std::string& str, char delim)
{
	std::istringstream iss(str);
	std::string token;
	auto res = std::make_shared<std::vector<std::string>>();
	while (std::getline(iss, token, delim)) {
		res->push_back(token);
	}

	return res;
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

	shared_ptr<SetRes> new_set_res = make_shared<SetRes>(syn, joined_set);
	shared_ptr<TableRes> new_table_res = make_shared<TableRes>(table_res->GetSynMap(), joined_table);
	return pair<shared_ptr<SetRes>, shared_ptr<TableRes>>(new_set_res, new_table_res);
}

//std::shared_ptr<std::vector<std::vector<std::string>>> SpaAlgo::HashJoinTables(std::shared_ptr<TableRes> table1, std::shared_ptr<TableRes> table2)
//{
//	auto col_set_1 = table1->ColumnsSet();
//	auto col_set_2 = table2->ColumnsSet();
//	auto common_col = make_shared<unordered_set<string>>();
//	for (auto& col : *col_set_1) {
//		if (col_set_2->find(col) != col_set_2->end()) {
//			common_col->insert(col);
//		}
//	}
//
//	auto res = make_shared<vector<vector<string>>>();
//	if (common_col->empty()) {
//		return res;
//	}
//
//	// populate composite key set of table 1
//	unordered_map<tuple<string>> join_set;
//
//	return std::shared_ptr<std::vector<std::string>>();
//}

std::shared_ptr<TableRes> SpaAlgo::JoinTablesOfTwoCommonColumns(std::shared_ptr<TableRes> table1, std::shared_ptr<TableRes> table2)
{
	auto cols_1 = table1->Columns();
	auto cols_2 = table2->Columns();

	std::sort(cols_1->begin(), cols_1->end());
	std::sort(cols_2->begin(), cols_2->end());
	auto res_table = make_shared<vector<StrPair>>();
	assert(cols_1 == cols_2);

	for (auto& pair1 : *(table1->GetRows())) {
		for (auto& pair2 : *(table2->GetRows())) {
			if (pair1 == pair2) {
				res_table->push_back(pair1);
			}
		}
	}

	auto res = shared_ptr<TableRes>(new TableRes(table1->GetSynMap(), res_table));

	return res;
}
