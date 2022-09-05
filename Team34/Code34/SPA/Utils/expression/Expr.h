#pragma once

#include <string>

using std::string;

class Expr
{
protected:
	string post_expr_;

public:
	explicit Expr(string infix_expr);

	string GetPostfix() { return post_expr_; }
};

