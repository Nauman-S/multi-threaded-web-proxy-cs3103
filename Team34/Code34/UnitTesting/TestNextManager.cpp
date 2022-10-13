#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/PKB/manager/NextManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestNextManager)
	{
	private:
		NextManager next_manager_;
	public:
		TEST_METHOD(TestCheckNext)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(3, 5);
			next_manager_.SetNext(4, 3);
			Assert::IsTrue(next_manager_.CheckNext(1, 2));
			Assert::IsTrue(next_manager_.CheckNext(2, 3));
			Assert::IsTrue(next_manager_.CheckNext(3, 4));
			Assert::IsTrue(next_manager_.CheckNext(3, 5));
			Assert::IsTrue(next_manager_.CheckNext(4, 3));
			Assert::IsFalse(next_manager_.CheckNext(3, 3));
			Assert::IsFalse(next_manager_.CheckNext(3, 2));
			Assert::IsFalse(next_manager_.CheckNext(3, 1));
		}

		TEST_METHOD(TestIsEmpty)
		{
			Assert::IsTrue(next_manager_.IsEmpty());
			next_manager_.SetNext(1, 2);
			Assert::IsFalse(next_manager_.IsEmpty());
		}

		TEST_METHOD(TestGetNextStmtsFromStmt)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(4, 3);
			next_manager_.SetNext(3, 7);
			next_manager_.SetNext(7, 8);
			next_manager_.SetNext(7, 9);
			next_manager_.SetNext(8, 10);
			next_manager_.SetNext(9, 10);

			std::shared_ptr<std::unordered_set<StmtNum>> next_1 = next_manager_.GetNextStmtsFromStmt(1);
			Assert::IsTrue(next_1->find(2) != next_1->end());
			Assert::AreEqual(1, int(next_1->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> next_2 = next_manager_.GetNextStmtsFromStmt(2);
			Assert::IsTrue(next_2->find(3) != next_2->end());
			Assert::AreEqual(1, int(next_2->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> next_3 = next_manager_.GetNextStmtsFromStmt(3);
			Assert::IsTrue(next_3->find(4) != next_3->end());
			Assert::IsTrue(next_3->find(7) != next_3->end());
			Assert::AreEqual(2, int(next_3->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> next_4 = next_manager_.GetNextStmtsFromStmt(4);
			Assert::IsTrue(next_4->find(3) != next_4->end());
			Assert::AreEqual(1, int(next_4->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> next_7 = next_manager_.GetNextStmtsFromStmt(7);
			Assert::IsTrue(next_7->find(8) != next_7->end());
			Assert::IsTrue(next_7->find(9) != next_7->end());
			Assert::AreEqual(2, int(next_7->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> next_8 = next_manager_.GetNextStmtsFromStmt(8);
			Assert::IsTrue(next_8->find(10) != next_8->end());
			Assert::AreEqual(1, int(next_8->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> next_9 = next_manager_.GetNextStmtsFromStmt(9);
			Assert::IsTrue(next_9->find(10) != next_9->end());
			Assert::AreEqual(1, int(next_9->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> next_10 = next_manager_.GetNextStmtsFromStmt(10);
			Assert::AreEqual(0, int(next_10->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> next_11 = next_manager_.GetNextStmtsFromStmt(11);
			Assert::AreEqual(0, int(next_11->size()));
		}

		TEST_METHOD(TestGetPrevStmtsFromStmt)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(4, 3);
			next_manager_.SetNext(3, 7);
			next_manager_.SetNext(7, 8);
			next_manager_.SetNext(7, 9);
			next_manager_.SetNext(8, 10);
			next_manager_.SetNext(9, 10);

			std::shared_ptr<std::unordered_set<StmtNum>> prev_1 = next_manager_.GetPrevStmtsFromStmt(1);
			Assert::AreEqual(0, int(next_manager_.GetPrevStmtsFromStmt(1)->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> prev_2 = next_manager_.GetPrevStmtsFromStmt(2);
			Assert::IsTrue(prev_2->find(1) != prev_2->end());
			Assert::AreEqual(1, int(next_manager_.GetPrevStmtsFromStmt(2)->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> prev_3 = next_manager_.GetPrevStmtsFromStmt(3);
			Assert::IsTrue(prev_3->find(2) != prev_3->end());
			Assert::IsTrue(prev_3->find(4) != prev_3->end());
			Assert::AreEqual(2, int(prev_3->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> prev_4 = next_manager_.GetPrevStmtsFromStmt(4);
			Assert::IsTrue(prev_4->find(3) != prev_4->end());
			Assert::AreEqual(1, int(prev_4->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> prev_7 = next_manager_.GetPrevStmtsFromStmt(7);
			Assert::IsTrue(prev_7->find(3) != prev_7->end());
			Assert::AreEqual(1, int(prev_7->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> prev_8 = next_manager_.GetPrevStmtsFromStmt(8);
			Assert::IsTrue(prev_8->find(7) != prev_8->end());
			Assert::AreEqual(1, int(prev_8->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> prev_9 = next_manager_.GetPrevStmtsFromStmt(9);
			Assert::IsTrue(prev_9->find(7) != prev_9->end());
			Assert::AreEqual(1, int(prev_9->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> prev_10 = next_manager_.GetPrevStmtsFromStmt(10);
			Assert::IsTrue(prev_10->find(8) != prev_10->end());
			Assert::IsTrue(prev_10->find(9) != prev_10->end());
			Assert::AreEqual(2, int(prev_10->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> prev_11 = next_manager_.GetPrevStmtsFromStmt(11);
			Assert::AreEqual(0, int(prev_11->size()));
		}

		TEST_METHOD(TestGetAllNextStmts)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(4, 3);
			next_manager_.SetNext(3, 7);
			next_manager_.SetNext(7, 8);
			next_manager_.SetNext(7, 9);
			next_manager_.SetNext(8, 10);
			next_manager_.SetNext(9, 10);

			std::shared_ptr<std::unordered_set<StmtNum>> all_next = next_manager_.GetAllNextStmts();
			Assert::IsTrue(all_next->find(2) != all_next->end());
			Assert::IsTrue(all_next->find(3) != all_next->end());
			Assert::IsTrue(all_next->find(4) != all_next->end());
			Assert::IsTrue(all_next->find(7) != all_next->end());
			Assert::IsTrue(all_next->find(8) != all_next->end());
			Assert::IsTrue(all_next->find(9) != all_next->end());
			Assert::IsTrue(all_next->find(10) != all_next->end());
			Assert::AreEqual(7, int(all_next->size()));

			next_manager_.SetNext(11, 12);
			next_manager_.SetNext(12, 13);
			all_next = next_manager_.GetAllNextStmts();
			Assert::IsTrue(all_next->find(2) != all_next->end());
			Assert::IsTrue(all_next->find(3) != all_next->end());
			Assert::IsTrue(all_next->find(4) != all_next->end());
			Assert::IsTrue(all_next->find(7) != all_next->end());
			Assert::IsTrue(all_next->find(8) != all_next->end());
			Assert::IsTrue(all_next->find(9) != all_next->end());
			Assert::IsTrue(all_next->find(10) != all_next->end());
			Assert::IsTrue(all_next->find(12) != all_next->end());
			Assert::IsTrue(all_next->find(13) != all_next->end());
			Assert::AreEqual(9, int(all_next->size()));

			next_manager_.SetNext(14, 15);
			next_manager_.SetNext(15, 14);
			next_manager_.SetNext(15, 16);
			all_next = next_manager_.GetAllNextStmts();
			Assert::IsTrue(all_next->find(2) != all_next->end());
			Assert::IsTrue(all_next->find(3) != all_next->end());
			Assert::IsTrue(all_next->find(4) != all_next->end());
			Assert::IsTrue(all_next->find(7) != all_next->end());
			Assert::IsTrue(all_next->find(8) != all_next->end());
			Assert::IsTrue(all_next->find(9) != all_next->end());
			Assert::IsTrue(all_next->find(10) != all_next->end());
			Assert::IsTrue(all_next->find(12) != all_next->end());
			Assert::IsTrue(all_next->find(13) != all_next->end());
			Assert::IsTrue(all_next->find(14) != all_next->end());
			Assert::IsTrue(all_next->find(15) != all_next->end());
			Assert::IsTrue(all_next->find(16) != all_next->end());
			Assert::AreEqual(12, int(all_next->size()));
		}

		TEST_METHOD(TestGetAllPrevStmts)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(4, 3);
			next_manager_.SetNext(3, 7);
			next_manager_.SetNext(7, 8);
			next_manager_.SetNext(7, 9);
			next_manager_.SetNext(8, 10);
			next_manager_.SetNext(9, 10);

			std::shared_ptr<std::unordered_set<StmtNum>> all_prev = next_manager_.GetAllPrevStmts();
			Assert::IsTrue(all_prev->find(1) != all_prev->end());
			Assert::IsTrue(all_prev->find(2) != all_prev->end());
			Assert::IsTrue(all_prev->find(3) != all_prev->end());
			Assert::IsTrue(all_prev->find(4) != all_prev->end());
			Assert::IsTrue(all_prev->find(7) != all_prev->end());
			Assert::IsTrue(all_prev->find(8) != all_prev->end());
			Assert::IsTrue(all_prev->find(9) != all_prev->end());
			Assert::AreEqual(7, int(all_prev->size()));

			next_manager_.SetNext(11, 12);
			next_manager_.SetNext(12, 13);
			all_prev = next_manager_.GetAllPrevStmts();
			Assert::IsTrue(all_prev->find(1) != all_prev->end());
			Assert::IsTrue(all_prev->find(2) != all_prev->end());
			Assert::IsTrue(all_prev->find(3) != all_prev->end());
			Assert::IsTrue(all_prev->find(4) != all_prev->end());
			Assert::IsTrue(all_prev->find(7) != all_prev->end());
			Assert::IsTrue(all_prev->find(8) != all_prev->end());
			Assert::IsTrue(all_prev->find(9) != all_prev->end());
			Assert::IsTrue(all_prev->find(11) != all_prev->end());
			Assert::IsTrue(all_prev->find(12) != all_prev->end());
			Assert::AreEqual(9, int(all_prev->size()));

			next_manager_.SetNext(14, 15);
			next_manager_.SetNext(15, 14);
			next_manager_.SetNext(15, 16);
			all_prev = next_manager_.GetAllPrevStmts();
			Assert::IsTrue(all_prev->find(1) != all_prev->end());
			Assert::IsTrue(all_prev->find(2) != all_prev->end());
			Assert::IsTrue(all_prev->find(3) != all_prev->end());
			Assert::IsTrue(all_prev->find(4) != all_prev->end());
			Assert::IsTrue(all_prev->find(7) != all_prev->end());
			Assert::IsTrue(all_prev->find(8) != all_prev->end());
			Assert::IsTrue(all_prev->find(9) != all_prev->end());
			Assert::IsTrue(all_prev->find(11) != all_prev->end());
			Assert::IsTrue(all_prev->find(12) != all_prev->end());
			Assert::IsTrue(all_prev->find(14) != all_prev->end());
			Assert::IsTrue(all_prev->find(15) != all_prev->end());
			Assert::AreEqual(11, int(all_prev->size()));
		}

		TEST_METHOD(TestGetAllNextRelations)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(4, 3);
			Assert::AreEqual(4, int(next_manager_.GetAllNextRelations()->size()));
			next_manager_.SetNext(4, 3);
			Assert::AreEqual(4, int(next_manager_.GetAllNextRelations()->size()));
		}

		TEST_METHOD(TestCheckNextT)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(4, 3);
			next_manager_.SetNext(3, 7);
			next_manager_.SetNext(7, 8);
			next_manager_.SetNext(7, 9);
			next_manager_.SetNext(8, 10);
			next_manager_.SetNext(9, 10);
			Assert::IsTrue(next_manager_.CheckNextT(1, 3));
			Assert::IsTrue(next_manager_.CheckNextT(1, 9));
			Assert::IsTrue(next_manager_.CheckNextT(3, 3));
			Assert::IsTrue(next_manager_.CheckNextT(3, 9));
			Assert::IsTrue(next_manager_.CheckNextT(4, 3));
			Assert::IsFalse(next_manager_.CheckNextT(4, 2));
			Assert::IsFalse(next_manager_.CheckNextT(8, 9));
			Assert::IsFalse(next_manager_.CheckNextT(10, 9));
			Assert::IsFalse(next_manager_.CheckNextT(7, 1));
		}

		TEST_METHOD(TestGetAllNextStmtsFromStmt)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(4, 3);
			next_manager_.SetNext(3, 7);
			next_manager_.SetNext(7, 8);
			next_manager_.SetNext(7, 9);
			next_manager_.SetNext(8, 10);
			next_manager_.SetNext(9, 10);
			Assert::AreEqual(7, int(next_manager_.GetAllNextStmtsFromStmt(1)->size()));
			Assert::AreEqual(6, int(next_manager_.GetAllNextStmtsFromStmt(2)->size()));
			Assert::AreEqual(6, int(next_manager_.GetAllNextStmtsFromStmt(3)->size()));
			Assert::AreEqual(6, int(next_manager_.GetAllNextStmtsFromStmt(4)->size()));
			Assert::AreEqual(3, int(next_manager_.GetAllNextStmtsFromStmt(7)->size()));
			Assert::AreEqual(1, int(next_manager_.GetAllNextStmtsFromStmt(8)->size()));
			Assert::AreEqual(1, int(next_manager_.GetAllNextStmtsFromStmt(9)->size()));
			Assert::AreEqual(0, int(next_manager_.GetAllNextStmtsFromStmt(10)->size()));
			Assert::AreEqual(0, int(next_manager_.GetAllNextStmtsFromStmt(11)->size()));
		}

		TEST_METHOD(TestGetAllPrevStmtsFromStmt)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			next_manager_.SetNext(3, 4);
			next_manager_.SetNext(4, 3);
			next_manager_.SetNext(3, 7);
			next_manager_.SetNext(7, 8);
			next_manager_.SetNext(7, 9);
			next_manager_.SetNext(8, 10);
			next_manager_.SetNext(9, 10);
			Assert::AreEqual(0, int(next_manager_.GetAllPrevStmtsFromStmt(1)->size()));
			Assert::AreEqual(1, int(next_manager_.GetAllPrevStmtsFromStmt(2)->size()));
			Assert::AreEqual(4, int(next_manager_.GetAllPrevStmtsFromStmt(3)->size()));
			Assert::AreEqual(4, int(next_manager_.GetAllPrevStmtsFromStmt(4)->size()));
			Assert::AreEqual(4, int(next_manager_.GetAllPrevStmtsFromStmt(7)->size()));
			Assert::AreEqual(5, int(next_manager_.GetAllPrevStmtsFromStmt(8)->size()));
			Assert::AreEqual(5, int(next_manager_.GetAllPrevStmtsFromStmt(9)->size()));
			Assert::AreEqual(7, int(next_manager_.GetAllPrevStmtsFromStmt(10)->size()));
			Assert::AreEqual(0, int(next_manager_.GetAllPrevStmtsFromStmt(11)->size()));
		}

		TEST_METHOD(TestGetAllNextTRelations_Sequential)
		{
			next_manager_.SetCodeBlock(1, 3);
			Assert::AreEqual(3, int(next_manager_.GetAllNextTRelations()->size()));
			next_manager_.SetCodeBlock(4, 6);
			next_manager_.SetOptimisedCFGEdge(1, 4);
			Assert::AreEqual(15, int(next_manager_.GetAllNextTRelations()->size()));
		}

		TEST_METHOD(TestGetAllNextTRelations_WhileLoop)
		{
			next_manager_.SetCodeBlock(1, 2);
			next_manager_.SetCodeBlock(3, 3);
			next_manager_.SetOptimisedCFGEdge(1, 3);
			next_manager_.SetCodeBlock(4, 5);
			next_manager_.SetOptimisedCFGEdge(3, 4);
			next_manager_.SetOptimisedCFGEdge(4, 3);
			next_manager_.SetCodeBlock(6, 7);
			next_manager_.SetOptimisedCFGEdge(3, 6);
			Assert::AreEqual(27, int(next_manager_.GetAllNextTRelations()->size()));
		}

		TEST_METHOD(TestGetAllNextTRelations_IfElse)
		{
			next_manager_.SetCodeBlock(1, 2);
			next_manager_.SetCodeBlock(3, 3);
			next_manager_.SetCodeBlock(4, 5);
			next_manager_.SetCodeBlock(6, 7);
			next_manager_.SetCodeBlock(8, 8);
			next_manager_.SetOptimisedCFGEdge(1, 3);
			next_manager_.SetOptimisedCFGEdge(3, 4);
			next_manager_.SetOptimisedCFGEdge(3, 6);
			next_manager_.SetOptimisedCFGEdge(4, 8);
			next_manager_.SetOptimisedCFGEdge(6, 8);
			Assert::AreEqual(24, int(next_manager_.GetAllNextTRelations()->size()));
		}

		TEST_METHOD(TestGetAllNextTRelations_NestedWhileIfElse)
		{
			next_manager_.SetCodeBlock(1, 2);
			next_manager_.SetCodeBlock(3, 3);
			next_manager_.SetCodeBlock(4, 5);
			next_manager_.SetCodeBlock(6, 7);
			next_manager_.SetCodeBlock(8, 8);
			next_manager_.SetOptimisedCFGEdge(1, 3);
			next_manager_.SetOptimisedCFGEdge(3, 4);
			next_manager_.SetOptimisedCFGEdge(3, 6);
			next_manager_.SetOptimisedCFGEdge(4, 3);
			next_manager_.SetOptimisedCFGEdge(6, 3);
			next_manager_.SetOptimisedCFGEdge(3, 8);
			Assert::AreEqual(43, int(next_manager_.GetAllNextTRelations()->size()));
		}

		TEST_METHOD(TestGetAllNextTRelations_NestedIfElseWhile)
		{
			next_manager_.SetCodeBlock(1, 2);
			next_manager_.SetCodeBlock(3, 3);
			next_manager_.SetCodeBlock(4, 5);
			next_manager_.SetCodeBlock(6, 6);
			next_manager_.SetCodeBlock(7, 7);
			next_manager_.SetCodeBlock(8, 8);
			next_manager_.SetOptimisedCFGEdge(1, 3);
			next_manager_.SetOptimisedCFGEdge(3, 4);
			next_manager_.SetOptimisedCFGEdge(3, 6);
			next_manager_.SetOptimisedCFGEdge(6, 7);
			next_manager_.SetOptimisedCFGEdge(7, 6);
			next_manager_.SetOptimisedCFGEdge(4, 8);
			next_manager_.SetOptimisedCFGEdge(6, 8);
			Assert::AreEqual(27, int(next_manager_.GetAllNextTRelations()->size()));
		}
	};
}