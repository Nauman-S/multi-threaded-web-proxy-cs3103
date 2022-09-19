#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/PKB/manager/PatternManager.h"
#include "../SPA/Utils/expression/Expr.h"
#include "../SPA/Utils/expression/PartialExprSpec.h"
#include "../SPA/Utils/expression/ExactExprSpec.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPatternManager)
	{
	private:
		PatternManager pattern_manager_;
	public:
		TEST_METHOD(TestIsAssignPatternMatch)
		{
			Expr expr = Expr("a + b * c");
			pattern_manager_.AddAssignPattern(1, "d", expr);
			PartialExprSpec partial_expr_valid = PartialExprSpec("b * c");
			Assert::IsTrue(pattern_manager_.IsAssignPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_valid)));
			PartialExprSpec partial_expr_invalid = PartialExprSpec("a + b");
			Assert::IsFalse(pattern_manager_.IsAssignPatternMatch(1, std::make_shared<PartialExprSpec>(partial_expr_invalid)));
			ExactExprSpec exact_expr_valid = ExactExprSpec("a + b * c");
			Assert::IsTrue(pattern_manager_.IsAssignPatternMatch(1, std::make_shared<ExactExprSpec>(exact_expr_valid)));
			ExactExprSpec exact_expr_invalid = ExactExprSpec("a + b * d");
			Assert::IsFalse(pattern_manager_.IsAssignPatternMatch(1, std::make_shared<ExactExprSpec>(exact_expr_invalid)));
		}

		TEST_METHOD(TestIsAssignPatternMatchWithVariable)
		{
			Expr expr = Expr("a + b * c");
			pattern_manager_.AddAssignPattern(1, "d", expr);
			PartialExprSpec partial_expr_valid = PartialExprSpec("b * c");
			Assert::IsTrue(pattern_manager_.IsAssignPatternMatch(1, "d", std::make_shared<PartialExprSpec>(partial_expr_valid)));
			Assert::IsFalse(pattern_manager_.IsAssignPatternMatch(1, "e", std::make_shared<PartialExprSpec>(partial_expr_valid)));
			PartialExprSpec partial_expr_invalid = PartialExprSpec("a + b");
			Assert::IsFalse(pattern_manager_.IsAssignPatternMatch(1, "d", std::make_shared<PartialExprSpec>(partial_expr_invalid)));
			Assert::IsFalse(pattern_manager_.IsAssignPatternMatch(1, "e", std::make_shared<PartialExprSpec>(partial_expr_invalid)));
			ExactExprSpec exact_expr_valid = ExactExprSpec("a + b * c");
			Assert::IsTrue(pattern_manager_.IsAssignPatternMatch(1, "d", std::make_shared<ExactExprSpec>(exact_expr_valid)));
			Assert::IsFalse(pattern_manager_.IsAssignPatternMatch(1, "e", std::make_shared<ExactExprSpec>(exact_expr_valid)));
			ExactExprSpec exact_expr_invalid = ExactExprSpec("a + b * d");
			Assert::IsFalse(pattern_manager_.IsAssignPatternMatch(1, "d", std::make_shared<ExactExprSpec>(exact_expr_invalid)));
			Assert::IsFalse(pattern_manager_.IsAssignPatternMatch(1, "e", std::make_shared<ExactExprSpec>(exact_expr_invalid)));
		}

		TEST_METHOD(TestGetAssignPatternMatch)
		{
			Expr expr1 = Expr("a + b * c");
			pattern_manager_.AddAssignPattern(1, "d", expr1);
			Expr expr2 = Expr("b * c * a");
			pattern_manager_.AddAssignPattern(2, "e", expr2);
			PartialExprSpec partial_expr = PartialExprSpec("b * c");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> patterns = pattern_manager_.GetAssignPatternMatch(std::make_shared<PartialExprSpec>(partial_expr));
			Assert::AreEqual(2, int(patterns->size()));
			PartialExprSpec partial_expr2 = PartialExprSpec("a + b");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> patterns2 = pattern_manager_.GetAssignPatternMatch(std::make_shared<PartialExprSpec>(partial_expr2));
			Assert::AreEqual(0, int(patterns2->size()));
			ExactExprSpec exact_expr = ExactExprSpec("a + b * c");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> patterns3 = pattern_manager_.GetAssignPatternMatch(std::make_shared<ExactExprSpec>(exact_expr));
			Assert::AreEqual(1, int(patterns3->size()));
			ExactExprSpec exact_expr2 = ExactExprSpec("a * b * c");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> patterns4 = pattern_manager_.GetAssignPatternMatch(std::make_shared<ExactExprSpec>(exact_expr2));
			Assert::AreEqual(0, int(patterns4->size()));
		}
	};
}