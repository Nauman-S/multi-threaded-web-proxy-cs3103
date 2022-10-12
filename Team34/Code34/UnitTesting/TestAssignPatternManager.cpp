#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include <memory>

#include "../SPA/PKB/manager/AssignPatternManager.h"
#include "../SPA/Utils/expression/Expr.h"
#include "../SPA/Utils/expression/PartialExprSpec.h"
#include "../SPA/Utils/expression/ExactExprSpec.h"
#include "../SPA/Utils/algo/PostfixConverter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
    TEST_CLASS(TestAssignPatternManager) {
private:
    AssignPatternManager assign_pattern_manager_;
public:
    TEST_METHOD(TestIsAssignPatternMatch) {
        PostfixConverter converter;
        std::string infix = "a + b * c % d / (e + f % g) + aa * bb % cc";
        Expr expr = Expr(infix, converter.InfixToPostfix(infix));
        assign_pattern_manager_.AddPattern(1, expr);

        // Test Exact expr matching
        infix = "a + b * c % d / (e + f % g) + aa * bb % cc";
        ExactExprSpec exact_expr_valid = ExactExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<ExactExprSpec>(exact_expr_valid)));

        infix = "aa * bb % cc";
        ExactExprSpec exact_expr_invalid = ExactExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<ExactExprSpec>(exact_expr_invalid)));

        // Test partial expr matching
        infix = "b * c % d";
        PartialExprSpec partial_expr_valid = PartialExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_valid)));

        infix = "e+f % g";
        partial_expr_valid = PartialExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_valid)));

        infix = "aa * bb";
        partial_expr_valid = PartialExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_valid)));

        infix = "a + b";
        PartialExprSpec partial_expr_invalid = PartialExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_invalid)));

        infix = "e + f";
        partial_expr_invalid = PartialExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_invalid)));

        infix = "bb % cc";
        partial_expr_invalid = PartialExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_invalid)));

        infix = "a * b";
        partial_expr_invalid = PartialExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_invalid)));

        infix = "aa * b";
        partial_expr_invalid = PartialExprSpec(infix, converter.InfixToPostfix(infix));
        Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_invalid)));
    }
    };
}