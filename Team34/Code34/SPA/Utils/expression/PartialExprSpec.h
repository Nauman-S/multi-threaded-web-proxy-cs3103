#pragma once
#include "ExprSpec.h"
#include "Expr.h"

class PartialExprSpec :
    public ExprSpec
{
public:
    PartialExprSpec(std::string infix_expr) : ExprSpec{ infix_expr } {};

    bool IsMatch(Expr& expr) override;

    bool IsWildcard() override { return false; }
};

