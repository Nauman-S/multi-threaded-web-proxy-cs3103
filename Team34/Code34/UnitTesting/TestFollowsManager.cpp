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
			std::shared_ptr<std::unordered_set<StmtNum>> successor_1 = follows_manager_.GetSuccessorStmtFromStmt(1);
			Assert::IsTrue(successor_1->find(2) != successor_1->end());

			std::shared_ptr<std::unordered_set<StmtNum>> successor_2 = follows_manager_.GetSuccessorStmtFromStmt(2);
			Assert::AreEqual(0, int(successor_2->size()));
		}

		TEST_METHOD(TestGetPredecessorStmtFromStmt)
		{
			follows_manager_.SetFollows(1, 2);
			std::shared_ptr<std::unordered_set<StmtNum>> predecessor_1 = follows_manager_.GetPredecessorStmtFromStmt(1);
			Assert::AreEqual(0, int(predecessor_1->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> predecessor_2 = follows_manager_.GetPredecessorStmtFromStmt(2);
			Assert::IsTrue(predecessor_2->find(1) != predecessor_2->end());
		}

		TEST_METHOD(TestGetAllPredecessorStmts)
		{
			Assert::AreEqual(0, int(follows_manager_.GetAllPredecessorStmts()->size()));

			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			follows_manager_.SetFollows(4, 5);

			std::shared_ptr<std::unordered_set<StmtNum>> all_predecessor = follows_manager_.GetAllPredecessorStmts();
			Assert::IsTrue(all_predecessor->find(1) != all_predecessor->end());
			Assert::IsTrue(all_predecessor->find(2) != all_predecessor->end());
			Assert::IsTrue(all_predecessor->find(4) != all_predecessor->end());
			Assert::AreEqual(3, int(all_predecessor->size()));
		}

		TEST_METHOD(TestGetAllSuccessorStmts)
		{
			Assert::AreEqual(0, int(follows_manager_.GetAllSuccessorStmts()->size()));

			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			follows_manager_.SetFollows(4, 5);

			std::shared_ptr<std::unordered_set<StmtNum>> all_successor = follows_manager_.GetAllSuccessorStmts();
			Assert::IsTrue(all_successor->find(2) != all_successor->end());
			Assert::IsTrue(all_successor->find(3) != all_successor->end());
			Assert::IsTrue(all_successor->find(5) != all_successor->end());
			Assert::AreEqual(3, int(all_successor->size()));
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

			std::shared_ptr<std::unordered_set<StmtNum>> successor_1 = follows_manager_.GetAllSuccessorStmtsFromStmt(1);
			Assert::IsTrue(successor_1->find(2) != successor_1->end());
			Assert::IsTrue(successor_1->find(3) != successor_1->end());

			std::shared_ptr<std::unordered_set<StmtNum>> successor_2 = follows_manager_.GetAllSuccessorStmtsFromStmt(2);
			Assert::IsTrue(successor_2->find(3) != successor_2->end());

			std::shared_ptr<std::unordered_set<StmtNum>> successor_3 = follows_manager_.GetAllSuccessorStmtsFromStmt(3);
			Assert::AreEqual(0, int(successor_3->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> successor_4 = follows_manager_.GetAllSuccessorStmtsFromStmt(4);
			Assert::IsTrue(successor_4->find(5) != successor_4->end());
		}

		TEST_METHOD(TestGetAllPredecessorStmtsFromStmt)
		{
			follows_manager_.SetFollows(1, 2);
			follows_manager_.SetFollows(2, 3);
			follows_manager_.SetFollows(4, 5);

			std::shared_ptr<std::unordered_set<StmtNum>> predecessor_1 = follows_manager_.GetAllPredecessorStmtsFromStmt(1);
			Assert::AreEqual(0, int(predecessor_1->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> predecessor_2 = follows_manager_.GetAllPredecessorStmtsFromStmt(2);
			Assert::IsTrue(predecessor_2->find(1) != predecessor_2->end());
		
			std::shared_ptr<std::unordered_set<StmtNum>> predecessor_3 = follows_manager_.GetAllPredecessorStmtsFromStmt(3);
			Assert::IsTrue(predecessor_3->find(1) != predecessor_3->end());
			Assert::IsTrue(predecessor_3->find(2) != predecessor_3->end());

			std::shared_ptr<std::unordered_set<StmtNum>> predecessor_5 = follows_manager_.GetAllPredecessorStmtsFromStmt(5);
			Assert::IsTrue(predecessor_5->find(4) != predecessor_5->end());
		}

		TEST_METHOD(TestGetAllFollowsTRelations)
		{
			Assert::AreEqual(0, int(follows_manager_.GetAllFollowsTRelations()->size()));
			follows_manager_.SetFollowsT(1, 2);
			follows_manager_.SetFollowsT(2, 3);
			follows_manager_.SetFollowsT(1, 3);
			Assert::AreEqual(3, int(follows_manager_.GetAllFollowsTRelations()->size()));
		}

		TEST_METHOD(TestClearFollowsStore)
		{
			follows_manager_.SetFollowsT(1, 2);
			Assert::AreEqual(1, int(follows_manager_.GetAllFollowsTRelations()->size()));
			follows_manager_.SetFollows(1, 2);
			Assert::AreEqual(1, int(follows_manager_.GetAllFollowsRelations()->size()));
			Assert::AreEqual(1, int(follows_manager_.GetPredecessorStmtFromStmt(2)->size()));
			Assert::AreEqual(1, int(follows_manager_.GetSuccessorStmtFromStmt(1)->size()));

			follows_manager_.Clear();
			Assert::AreEqual(0, int(follows_manager_.GetAllFollowsTRelations()->size()));
			Assert::AreEqual(0, int(follows_manager_.GetAllFollowsRelations()->size()));
			Assert::AreEqual(0, int(follows_manager_.GetPredecessorStmtFromStmt(2)->size()));
			Assert::AreEqual(0, int(follows_manager_.GetSuccessorStmtFromStmt(1)->size()));
		}
	};
}