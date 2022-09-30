#pragma once
#include "ExprSpec.h"
#include "Expr.h"

class ExactExprSpec :
    public ExprSpec
{
public:
    ExactExprSpec(string infix_expr) : ExprSpec{ infix_expr } {};

    bool IsMatch(Expr& expr) override;

    bool IsWildcard() override { return false; }
};

