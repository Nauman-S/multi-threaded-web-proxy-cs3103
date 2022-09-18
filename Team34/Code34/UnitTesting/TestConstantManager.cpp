#include <memory>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/manager/ConstantManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestConstantManager)
	{
	private:
		ConstantManager constant_manager_;
	public:
		TEST_METHOD(TestAddConstant)
		{
			Assert::AreEqual(0, int(constant_manager_.GetAllEntities()->size()));
			constant_manager_.AddEntity(1);
			Assert::AreEqual(1, int(constant_manager_.GetAllEntities()->size()));
		};

		TEST_METHOD(TestIsConstant)
		{
			constant_manager_.AddEntity(1);
			Assert::IsTrue(constant_manager_.IsEntity(1));
			Assert::IsFalse(constant_manager_.IsEntity(2));
		};

		TEST_METHOD(TestGetAllConstants)
		{
			constant_manager_.AddEntity(1);
			constant_manager_.AddEntity(2);
			constant_manager_.AddEntity(3);
			Assert::AreEqual(3, int(constant_manager_.GetAllEntities()->size()));
		};
	};
}