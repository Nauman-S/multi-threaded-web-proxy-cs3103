#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/PKB/manager/WhilePatternManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestWhilePatternManager)
	{
	private:
		WhilePatternManager while_pattern_manager_;
	public:
		TEST_METHOD(GetAllWhileStatmentsFromVar)
		{
			while_pattern_manager_.AddPattern(1, "x");
			while_pattern_manager_.AddPattern(2, "y");
			Assert::AreEqual(1, int(while_pattern_manager_.GetAllStatmentsFromVar("x")->size()));
			Assert::AreEqual(1, int(while_pattern_manager_.GetAllStatmentsFromVar("y")->size()));
			while_pattern_manager_.AddPattern(2, "x");
			Assert::AreEqual(2, int(while_pattern_manager_.GetAllStatmentsFromVar("x")->size()));
		}

		TEST_METHOD(GetAllWhileStatements)
		{
			while_pattern_manager_.AddPattern(1, "x");
			while_pattern_manager_.AddPattern(2, "y");
			Assert::AreEqual(2, int(while_pattern_manager_.GetAllStatements()->size()));
			while_pattern_manager_.AddPattern(2, "x");
			Assert::AreEqual(2, int(while_pattern_manager_.GetAllStatements()->size()));
		}

		TEST_METHOD(GetAllWhilePatterns)
		{
			while_pattern_manager_.AddPattern(1, "x");
			while_pattern_manager_.AddPattern(2, "y");
			Assert::AreEqual(2, int(while_pattern_manager_.GetAllPatterns()->size()));
			while_pattern_manager_.AddPattern(2, "x");
			Assert::AreEqual(3, int(while_pattern_manager_.GetAllPatterns()->size()));
		}
	};
}