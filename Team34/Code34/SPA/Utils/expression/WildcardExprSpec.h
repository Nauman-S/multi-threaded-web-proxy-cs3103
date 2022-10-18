#pragma once

#include "ExprSpec.h"
#include "Expr.h"

class WildcardExprSpec : public ExprSpec {
public:
    WildcardExprSpec() : ExprSpec{ "", "" } {};

    bool IsMatch(Expr& expr) override { return true; };

    bool IsWildcard() override { return true; }
};

