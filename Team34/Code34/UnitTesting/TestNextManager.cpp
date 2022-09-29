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

		TEST_METHOD(TestCheckNext)
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


	};
}