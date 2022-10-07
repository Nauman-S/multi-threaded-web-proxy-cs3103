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
			Assert::AreEqual(1, int(next_manager_.GetNextStmtsFromStmt(1)->size()));
			Assert::AreEqual(1, int(next_manager_.GetNextStmtsFromStmt(2)->size()));
			Assert::AreEqual(2, int(next_manager_.GetNextStmtsFromStmt(3)->size()));
			Assert::AreEqual(1, int(next_manager_.GetNextStmtsFromStmt(4)->size()));
			Assert::AreEqual(2, int(next_manager_.GetNextStmtsFromStmt(7)->size()));
			Assert::AreEqual(1, int(next_manager_.GetNextStmtsFromStmt(8)->size()));
			Assert::AreEqual(1, int(next_manager_.GetNextStmtsFromStmt(9)->size()));
			Assert::AreEqual(0, int(next_manager_.GetNextStmtsFromStmt(10)->size()));
			Assert::AreEqual(0, int(next_manager_.GetNextStmtsFromStmt(11)->size()));
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
			Assert::AreEqual(0, int(next_manager_.GetPrevStmtsFromStmt(1)->size()));
			Assert::AreEqual(1, int(next_manager_.GetPrevStmtsFromStmt(2)->size()));
			Assert::AreEqual(2, int(next_manager_.GetPrevStmtsFromStmt(3)->size()));
			Assert::AreEqual(1, int(next_manager_.GetPrevStmtsFromStmt(4)->size()));
			Assert::AreEqual(1, int(next_manager_.GetPrevStmtsFromStmt(7)->size()));
			Assert::AreEqual(1, int(next_manager_.GetPrevStmtsFromStmt(8)->size()));
			Assert::AreEqual(1, int(next_manager_.GetPrevStmtsFromStmt(9)->size()));
			Assert::AreEqual(2, int(next_manager_.GetPrevStmtsFromStmt(10)->size()));
			Assert::AreEqual(0, int(next_manager_.GetPrevStmtsFromStmt(11)->size()));
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
			Assert::AreEqual(7, int(next_manager_.GetAllNextStmts()->size()));
			next_manager_.SetNext(11, 12);
			next_manager_.SetNext(12, 13);
			Assert::AreEqual(9, int(next_manager_.GetAllNextStmts()->size()));
			next_manager_.SetNext(14, 15);
			next_manager_.SetNext(15, 14);
			next_manager_.SetNext(15, 16);
			Assert::AreEqual(12, int(next_manager_.GetAllNextStmts()->size()));
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
			Assert::AreEqual(7, int(next_manager_.GetAllPrevStmts()->size()));
			next_manager_.SetNext(11, 12);
			next_manager_.SetNext(12, 13);
			Assert::AreEqual(9, int(next_manager_.GetAllPrevStmts()->size()));
			next_manager_.SetNext(14, 15);
			next_manager_.SetNext(15, 14);
			next_manager_.SetNext(15, 16);
			Assert::AreEqual(11, int(next_manager_.GetAllPrevStmts()->size()));
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

		TEST_METHOD(TestGetAllNextTRelations)
		{
			next_manager_.SetNext(1, 2);
			next_manager_.SetNext(2, 3);
			Assert::AreEqual(3, int(next_manager_.GetAllNextTRelations()->size()));
			next_manager_.SetNext(3, 6);
			next_manager_.SetNext(4, 6);
			next_manager_.SetNext(6, 7);
			Assert::AreEqual(12, int(next_manager_.GetAllNextTRelations()->size()));
			next_manager_.SetNext(4, 5);
			next_manager_.SetNext(5, 4);
			Assert::AreEqual(18, int(next_manager_.GetAllNextTRelations()->size()));
		}
	};
}