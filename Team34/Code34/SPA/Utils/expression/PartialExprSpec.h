#pragma once
#include "ExprSpec.h"
#include "Expr.h"

class PartialExprSpec :
    public ExprSpec
{
public:
    PartialExprSpec(std::string infix_str, std::string postfix_str) : ExprSpec{ infix_str, postfix_str } {};

    bool IsMatch(Expr& expr) override;

    bool IsWildcard() override { return false; }
};

