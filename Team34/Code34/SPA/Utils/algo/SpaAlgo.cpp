#include "SpaAlgo.h"

#include <string>
#include <stack>
#include <sstream>
#include <cassert>

using std::string;
using std::stack;

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
		if (iter == '(') {
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
