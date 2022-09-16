#pragma once

#include <string>

#include "Expr.h"

class ExprSpec
{
protected:
	std::string infix_expr_;
	std::string post_expr_;

public:
	ExprSpec(std::string infix_expr);

	virtual bool IsMatch(Expr expr) = 0;
	virtual bool IsWildcard() = 0;
	string GetInfix() { return infix_expr_; }
	string GetPostfix() { return post_expr_; }
};

