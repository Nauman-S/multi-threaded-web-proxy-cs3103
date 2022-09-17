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
		TEST_METHOD(TestSetFollows)
		{
			follows_manager_.SetFollows(1, 2);
			Assert::AreEqual(1, int(follows_manager_.GetAllFollowsRelations()->size()));
			follows_manager_.SetFollows(2, 1);
			Assert::AreEqual(1, int(follows_manager_.GetAllFollowsRelations()->size()));
			follows_manager_.SetFollows(1, 3);
			Assert::AreEqual(1, int(follows_manager_.GetAllFollowsRelations()->size()));
		}

		TEST_METHOD(TestCheckFollows)
		{
			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			Assert::IsTrue(follows_manager_.CheckFollows(1, 2));
			Assert::IsTrue(follows_manager_.CheckFollows(2, 3));
			Assert::IsFalse(follows_manager_.CheckFollows(1, 3));
			Assert::IsFalse(follows_manager_.CheckFollows(2, 1));
		}

		TEST_METHOD(TestIsEmpty)
		{
			Assert::IsTrue(follows_manager_.IsEmpty());
			follows_manager_.SetFollows(1, 2);
			Assert::IsFalse(follows_manager_.IsEmpty());
		}

		TEST_METHOD(TestGetSuccessorStmtFromStmt)
		{
			follows_manager_.SetFollows(1, 2);
			Assert::AreEqual(2, follows_manager_.GetSuccessorStmtFromStmt(1));
			Assert::AreEqual(0, follows_manager_.GetSuccessorStmtFromStmt(2));
		}

		TEST_METHOD(TestGetPredecessorStmtFromStmt)
		{
			follows_manager_.SetFollows(1, 2);
			Assert::AreEqual(1, follows_manager_.GetPredecessorStmtFromStmt(2));
			Assert::AreEqual(0, follows_manager_.GetPredecessorStmtFromStmt(1));
		}

		TEST_METHOD(TestGetAllPredecessorStmts)
		{
			Assert::AreEqual(0, int(follows_manager_.GetAllPredecessorStmts()->size()));
			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			follows_manager_.SetFollows(4, 5);
			Assert::AreEqual(3, int(follows_manager_.GetAllPredecessorStmts()->size()));
		}

		TEST_METHOD(TestGetAllSuccessorStmts)
		{
			Assert::AreEqual(0, int(follows_manager_.GetAllSuccessorStmts()->size()));
			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			follows_manager_.SetFollows(4, 5);
			Assert::AreEqual(3, int(follows_manager_.GetAllSuccessorStmts()->size()));
		}

		TEST_METHOD(TestGetAllFollowsRelations)
		{
			Assert::AreEqual(0, int(follows_manager_.GetAllFollowsRelations()->size()));
			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			Assert::AreEqual(2, int(follows_manager_.GetAllFollowsRelations()->size()));
		}

		TEST_METHOD(TestSetFollowsT)
		{
			follows_manager_.SetFollowsT(1, 2);
			Assert::AreEqual(1, int(follows_manager_.GetAllFollowsTRelations()->size()));
			follows_manager_.SetFollowsT(2, 1);
			Assert::AreEqual(1, int(follows_manager_.GetAllFollowsTRelations()->size()));
		}

		TEST_METHOD(TestCheckFollowsT)
		{
			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			Assert::IsTrue(follows_manager_.CheckFollowsT(1, 2));
			Assert::IsTrue(follows_manager_.CheckFollowsT(2, 3));
			Assert::IsTrue(follows_manager_.CheckFollowsT(1, 3));
			Assert::IsFalse(follows_manager_.CheckFollowsT(2, 1));
		}

		TEST_METHOD(TestGetAllSuccessorStmtsFromStmt)
		{
			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			follows_manager_.SetFollows(4, 5);
			Assert::AreEqual(2, int(follows_manager_.GetAllSuccessorStmtsFromStmt(1)->size()));
			Assert::AreEqual(1, int(follows_manager_.GetAllSuccessorStmtsFromStmt(2)->size()));
			Assert::AreEqual(0, int(follows_manager_.GetAllSuccessorStmtsFromStmt(3)->size()));
			Assert::AreEqual(1, int(follows_manager_.GetAllSuccessorStmtsFromStmt(4)->size()));
		}

		TEST_METHOD(TestGetAllPredecessorStmtsFromStmt)
		{
			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			follows_manager_.SetFollows(4, 5);
			Assert::AreEqual(2, int(follows_manager_.GetAllPredecessorStmtsFromStmt(3)->size()));
			Assert::AreEqual(1, int(follows_manager_.GetAllPredecessorStmtsFromStmt(2)->size()));
			Assert::AreEqual(0, int(follows_manager_.GetAllPredecessorStmtsFromStmt(1)->size()));
			Assert::AreEqual(1, int(follows_manager_.GetAllPredecessorStmtsFromStmt(5)->size()));
		}

		TEST_METHOD(TestGetAllFollowsTRelations)
		{
			Assert::AreEqual(0, int(follows_manager_.GetAllFollowsTRelations()->size()));
			follows_manager_.SetFollowsT(1, 2);
			follows_manager_.SetFollowsT(2, 3);
			follows_manager_.SetFollowsT(1, 3);
			Assert::AreEqual(3, int(follows_manager_.GetAllFollowsTRelations()->size()));
		}
	};
}