#pragma once
#include "ExprSpec.h"
#include "Expr.h"

class PartialExprSpec :
    public ExprSpec
{
public:
    bool IsMatch(Expr expr) override;
};

