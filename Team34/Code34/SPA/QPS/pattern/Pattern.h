#pragma once
#include "../reference/AssignRef.h"
#include "../reference/VarRef.h"
#include "../../Utils/expression/ExprSpec.h"
class Pattern
{
protected:
	AssignRef& assign_;
	VarRef& lhs_;
	ExprSpec& rhs_;

};

