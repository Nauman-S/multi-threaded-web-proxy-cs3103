#pragma once
#include "ExprSpec.h"
#include "Expr.h"
class WildcardExprSpec :
    public ExprSpec
{
public:
    bool IsMatch(Expr expr) override { return true; };
};

