#include "PostfixConverter.h"

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <sstream>

using std::string;
using std::stack;
using std::vector;


std::shared_ptr<std::vector<std::string>> PostfixConverter::Split(std::string& str, char delim)
{
	std::istringstream iss(str);
	std::string token;
	auto res = std::make_shared<std::vector<std::string>>();
	while (std::getline(iss, token, delim)) {
		res->push_back(token);
	}

	return res;
}

std::string PostfixConverter::InfixToPostfix(std::string& infix)
{
	if (infix == "") {
		return "";
	}

	stack<string> stk;
	vector<string> postfix_tokens;

	auto splited = Split(infix, DELIM);
	for (string& token : *splited) {
		if (token == " ") {
			continue;
		}
		else if (token == "(") {
			stk.push(token);
		}
		else if (token == ")") {
			while (!stk.empty() && stk.top() != "(") {
				postfix_tokens.push_back(stk.top());
				stk.pop();
			}
			stk.pop();  // discard the "("
		}
		else if (auto p = precedence_.find(token); p != precedence_.end()) {
			while (!stk.empty() && stk.top() != "(" && precedence_[stk.top()] >= p->second) {
				// assume all operators are left-associative
				postfix_tokens.push_back(stk.top());
				stk.pop();
			}
			stk.push(token);
		}
		else {  // is not an operator
			postfix_tokens.push_back(token);
		}
	}

	while (!stk.empty()) {
		postfix_tokens.push_back(stk.top());
		stk.pop();
	}

	string postfix = postfix_tokens[0];
	for (int i = 1; i < postfix_tokens.size(); ++i) {
		postfix += (DELIM + postfix_tokens[i]);
	}

	return postfix;
}
