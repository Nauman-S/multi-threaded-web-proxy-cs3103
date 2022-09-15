#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/PKB/manager/FollowsManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestFollowsManager)
	{
	private:
		FollowsManager follows_manager_;
	public:
		TEST_METHOD(TestSetFollows) {
			follows_manager_.SetFollows(1, 2);
			Assert::AreEqual(1, int(follows_manager_.GetAllFollowsRelations()->size()));
		}
	};
}