#include <memory>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/manager/VariableManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestVariableManager)
	{
	private:
		VariableManager variable_manager_;
	public:
		TEST_METHOD(TestAddVariable)
		{
			Assert::AreEqual(0, int(variable_manager_.GetAllEntities()->size()));
			variable_manager_.AddEntity("a");
			Assert::AreEqual(1, int(variable_manager_.GetAllEntities()->size()));
		};

		TEST_METHOD(TestIsVariable)
		{
			variable_manager_.AddEntity("a");
			Assert::IsTrue(variable_manager_.IsEntity("a"));
			Assert::IsFalse(variable_manager_.IsEntity("b"));
		};

		TEST_METHOD(TestGetAllVariables)
		{
			variable_manager_.AddEntity("a");
			variable_manager_.AddEntity("b");
			variable_manager_.AddEntity("c");
			Assert::AreEqual(3, int(variable_manager_.GetAllEntities()->size()));
		};

		TEST_METHOD(TestClearVariableStore)
		{
			variable_manager_.AddEntity("a");
			Assert::AreEqual(1, int(variable_manager_.GetAllEntities()->size()));

			variable_manager_.Clear();
			Assert::AreEqual(0, int(variable_manager_.GetAllEntities()->size()));
		}
	};
}