#pragma once

#include <string>
#include <unordered_map>
#include <memory>


class PostfixConverter
{
protected:
	std::unordered_map<std::string, int> precedence_;

	std::shared_ptr<std::vector<std::string>> Split(std::string& str, char delim);

public:
	PostfixConverter()
		:precedence_{ { "+", 1}, { "-", 1 }, { "*", 2 }, { "/", 2 }, { "%", 2 } } {};

	static const char DELIM = ' ';

	std::string InfixToPostfix(std::string& infix);
};

