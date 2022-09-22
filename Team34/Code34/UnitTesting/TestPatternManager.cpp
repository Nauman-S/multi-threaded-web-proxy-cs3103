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
	TEST_CLASS(TestPatternManager)
	{
	private:
		AssignPatternManager assign_pattern_manager_;
	public:
		TEST_METHOD(TestIsAssignPatternMatch)
		{
			Expr expr = Expr("a + b * c");
			assign_pattern_manager_.AddPattern(1, "d", expr);
			PartialExprSpec partial_expr_valid = PartialExprSpec("b * c");
			Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_valid)));
			PartialExprSpec partial_expr_invalid = PartialExprSpec("a + b");
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_invalid)));
			ExactExprSpec exact_expr_valid = ExactExprSpec("a + b * c");
			Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<ExactExprSpec>(exact_expr_valid)));
			ExactExprSpec exact_expr_invalid = ExactExprSpec("a + b * d");
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, std::make_shared<ExactExprSpec>(exact_expr_invalid)));
		}

		TEST_METHOD(TestIsAssignPatternMatchWithVariable)
		{
			Expr expr = Expr("a + b * c");
			assign_pattern_manager_.AddPattern(1, "d", expr);
			PartialExprSpec partial_expr_valid = PartialExprSpec("b * c");
			Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, "d", std::make_shared<PartialExprSpec>(partial_expr_valid)));
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, "e", std::make_shared<PartialExprSpec>(partial_expr_valid)));
			PartialExprSpec partial_expr_invalid = PartialExprSpec("a + b");
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, "d", std::make_shared<PartialExprSpec>(partial_expr_invalid)));
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, "e", std::make_shared<PartialExprSpec>(partial_expr_invalid)));
			ExactExprSpec exact_expr_valid = ExactExprSpec("a + b * c");
			Assert::IsTrue(assign_pattern_manager_.IsPatternMatch(1, "d", std::make_shared<ExactExprSpec>(exact_expr_valid)));
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, "e", std::make_shared<ExactExprSpec>(exact_expr_valid)));
			ExactExprSpec exact_expr_invalid = ExactExprSpec("a + b * d");
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, "d", std::make_shared<ExactExprSpec>(exact_expr_invalid)));
			Assert::IsFalse(assign_pattern_manager_.IsPatternMatch(1, "e", std::make_shared<ExactExprSpec>(exact_expr_invalid)));
		}

		TEST_METHOD(TestGetAssignPatternMatch)
		{
			Expr expr1 = Expr("a + b * c");
			assign_pattern_manager_.AddPattern(1, "d", expr1);
			Expr expr2 = Expr("b * c * a");
			assign_pattern_manager_.AddPattern(2, "e", expr2);
			PartialExprSpec partial_expr = PartialExprSpec("b * c");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> patterns = assign_pattern_manager_.GetPatternMatch(std::make_shared<PartialExprSpec>(partial_expr));
			Assert::AreEqual(2, int(patterns->size()));
			PartialExprSpec partial_expr2 = PartialExprSpec("a + b");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> patterns2 = assign_pattern_manager_.GetPatternMatch(std::make_shared<PartialExprSpec>(partial_expr2));
			Assert::AreEqual(0, int(patterns2->size()));
			ExactExprSpec exact_expr = ExactExprSpec("a + b * c");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> patterns3 = assign_pattern_manager_.GetPatternMatch(std::make_shared<ExactExprSpec>(exact_expr));
			Assert::AreEqual(1, int(patterns3->size()));
			ExactExprSpec exact_expr2 = ExactExprSpec("a * b * c");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> patterns4 = assign_pattern_manager_.GetPatternMatch(std::make_shared<ExactExprSpec>(exact_expr2));
			Assert::AreEqual(0, int(patterns4->size()));
		}
	};
}