#pragma once

#include <string>

using std::string;

class Expr
{
protected:
	string infix_expr_;
	string post_expr_;

public:
	explicit Expr(string infix_expr);

	string GetInfix() { return infix_expr_; }
	string GetPostfix() { return post_expr_; }
};

