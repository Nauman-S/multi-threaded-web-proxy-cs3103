#pragma once
#include "Expr.h"

#include <string>

class ExprSpec
{
protected:
	std::string expr_;

public:
	virtual bool IsMatch(Expr expr) = 0;
};

