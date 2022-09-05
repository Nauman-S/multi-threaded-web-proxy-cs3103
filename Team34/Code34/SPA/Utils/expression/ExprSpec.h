#pragma once

#include <string>

#include "Expr.h"

class ExprSpec
{
protected:
	std::string post_expr_;

public:
	void ExprSepc(std::string infix_expr);

	virtual bool IsMatch(Expr expr) = 0;
};

