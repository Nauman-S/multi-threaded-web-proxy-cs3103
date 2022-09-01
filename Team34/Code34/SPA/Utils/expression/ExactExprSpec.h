#pragma once
#include "ExprSpec.h"
#include "Expr.h"

class ExactExprSpec :
    public ExprSpec
{
public:
    bool IsMatch(Expr expr) override;
};

