#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/PKB/manager/AssignPatternManager.h"
#include "../SPA/Utils/expression/Expr.h"
#include "../SPA/Utils/expression/PartialExprSpec.h"
#include "../SPA/Utils/expression/ExactExprSpec.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestAssignPatternManager)
	{
	private:
		AssignPatternManager assign_pattern_manager_;
	public:
		TEST_METHOD(TestIsAssignPatternMatch)
		{
			Expr expr = Expr("a + b * c");
			assign_pattern_manager_.AddPattern(1, expr);
			PartialExprSpec partial_expr_valid = PartialExprSpec("b * c");
			Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_valid)));
			PartialExprSpec partial_expr_invalid = PartialExprSpec("a + b");
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_invalid)));
			ExactExprSpec exact_expr_valid = ExactExprSpec("a + b * c");
			Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<ExactExprSpec>(exact_expr_valid)));
			ExactExprSpec exact_expr_invalid = ExactExprSpec("a + b * d");
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<ExactExprSpec>(exact_expr_invalid)));
		}
	};
}