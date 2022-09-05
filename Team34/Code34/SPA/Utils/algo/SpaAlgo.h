#pragma once

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class SpaAlgo
{
public:
	static string InfixToPostfix(string infix);

protected:
	static unordered_map<char, int> precedence_;
};

