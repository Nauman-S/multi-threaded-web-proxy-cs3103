#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/PKB/manager/IfPatternManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestIfPatternManager)
	{
	private:
		IfPatternManager if_pattern_manager_;
	public:
		TEST_METHOD(TestGetAllIfStatmentsFromVar)
		{
			if_pattern_manager_.AddPattern(1, "x");
			if_pattern_manager_.AddPattern(2, "y");
			Assert::AreEqual(1, int(if_pattern_manager_.GetAllStatmentsFromVar("x")->size()));
			Assert::AreEqual(1, int(if_pattern_manager_.GetAllStatmentsFromVar("y")->size()));
			if_pattern_manager_.AddPattern(2, "x");
			Assert::AreEqual(2, int(if_pattern_manager_.GetAllStatmentsFromVar("x")->size()));
		}

		TEST_METHOD(TestGetAllIfStatements)
		{
			if_pattern_manager_.AddPattern(1, "x");
			if_pattern_manager_.AddPattern(2, "y");
			Assert::AreEqual(2, int(if_pattern_manager_.GetAllStatements()->size()));
			if_pattern_manager_.AddPattern(2, "x");
			Assert::AreEqual(2, int(if_pattern_manager_.GetAllStatements()->size()));
		}

		TEST_METHOD(TestGetAllIfPatterns)
		{
			if_pattern_manager_.AddPattern(1, "x");
			if_pattern_manager_.AddPattern(2, "y");
			Assert::AreEqual(2, int(if_pattern_manager_.GetAllPatterns()->size()));
			if_pattern_manager_.AddPattern(2, "x");
			Assert::AreEqual(3, int(if_pattern_manager_.GetAllPatterns()->size()));
		}

		TEST_METHOD(TestClearIfPatternStore)
		{
			if_pattern_manager_.AddPattern(1, "x");
			Assert::AreEqual(1, int(if_pattern_manager_.GetAllPatterns()->size()));
			Assert::AreEqual(1, int(if_pattern_manager_.GetAllStatements()->size()));
			Assert::AreEqual(1, int(if_pattern_manager_.GetAllStatmentsFromVar("x")->size()));

			if_pattern_manager_.Clear();
			Assert::AreEqual(0, int(if_pattern_manager_.GetAllPatterns()->size()));
			Assert::AreEqual(0, int(if_pattern_manager_.GetAllStatements()->size()));
			Assert::AreEqual(0, int(if_pattern_manager_.GetAllStatmentsFromVar("x")->size()));
		}
	};
}