#pragma once

#include <string>

#include "Expr.h"
#include "../algo/SpaAlgo.h"


class ExprSpec
{
protected:
	std::string infix_expr_;
	std::string post_expr_;

public:
	ExprSpec(std::string infix_str) : infix_expr_{ infix_str }, post_expr_{ SpaAlgo::InfixToPostfix(infix_str) } {};

	ExprSpec(std::string infix_str, std::string postfix_str)
		: infix_expr_{ infix_str }, post_expr_{ postfix_str } {};

	virtual bool IsMatch(Expr& expr) = 0;

	virtual bool IsWildcard() = 0;

	std::string& GetInfix() { return infix_expr_; }

	std::string& GetPostfix() { return post_expr_; }
};

