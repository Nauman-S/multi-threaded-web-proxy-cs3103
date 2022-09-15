#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/PKB/manager/ParentManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestParentManager)
	{
	private:
		ParentManager parent_manager_;
	public:
		TEST_METHOD(TestSetParent) {
			parent_manager_.SetParent(1, 2);
			Assert::AreEqual(1, int(parent_manager_.GetAllParentRelations()->size()));
		}
	};
}