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
		TEST_METHOD(TestSetParent) 
		{
			parent_manager_.SetParent(1, 2);
			Assert::AreEqual(1, int(parent_manager_.GetAllParentRelations()->size()));
			parent_manager_.SetParent(1, 3);
			Assert::AreEqual(2, int(parent_manager_.GetAllParentRelations()->size()));
		}

		TEST_METHOD(TestCheckParent) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			Assert::IsTrue(parent_manager_.CheckParent(1, 2));
			Assert::IsTrue(parent_manager_.CheckParent(1, 3));
			Assert::IsFalse(parent_manager_.CheckParent(2, 3));
		}

		TEST_METHOD(TestIsEmpty) 
		{
			Assert::IsTrue(parent_manager_.IsEmpty());
			parent_manager_.SetParent(1, 2);
			Assert::IsFalse(parent_manager_.IsEmpty());
		}

		TEST_METHOD(TestGetChildrenFromStmt) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);
			Assert::AreEqual(2, int(parent_manager_.GetChildrenFromStmt(1)->size()));
		}

		TEST_METHOD(TestGetParentFromStmt) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);
			Assert::AreEqual(0, int(parent_manager_.GetParentFromStmt(1)->size()));
			Assert::AreEqual(1, int(parent_manager_.GetParentFromStmt(2)->size()));
			Assert::AreEqual(1, int(parent_manager_.GetParentFromStmt(3)->size()));
			Assert::AreEqual(1, int(parent_manager_.GetParentFromStmt(4)->size()));
		}

		TEST_METHOD(TestGetAllParents) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);
			Assert::AreEqual(2, int(parent_manager_.GetAllParents()->size()));
		}

		TEST_METHOD(TestGetAllChildren) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);
			Assert::AreEqual(3, int(parent_manager_.GetAllChildren()->size()));
		}

		TEST_METHOD(TestGetAllParentRelations) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);
			Assert::AreEqual(3, int(parent_manager_.GetAllParentRelations()->size()));
		}

		TEST_METHOD(TestSetParentT) 
		{
			parent_manager_.SetParentT(1, 2);
			Assert::AreEqual(1, int(parent_manager_.GetAllParentTRelations()->size()));
			parent_manager_.SetParentT(2, 1);
			Assert::AreEqual(1, int(parent_manager_.GetAllParentTRelations()->size()));
		}

		TEST_METHOD(TestCheckParentT)
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(2, 3);
			Assert::IsTrue(parent_manager_.CheckParentT(1, 2));
			Assert::IsTrue(parent_manager_.CheckParentT(1, 3));
			Assert::IsFalse(parent_manager_.CheckParentT(1, 4));
		}

		TEST_METHOD(TestGetAllChildrenFromStmt) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);
			Assert::AreEqual(3, int(parent_manager_.GetAllChildrenFromStmt(1)->size()));
			Assert::AreEqual(1, int(parent_manager_.GetAllChildrenFromStmt(2)->size()));
			Assert::AreEqual(0, int(parent_manager_.GetAllChildrenFromStmt(3)->size()));
		}

		TEST_METHOD(TestGetAllParentsFromStmt) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);
			Assert::AreEqual(0, int(parent_manager_.GetAllParentsFromStmt(1)->size()));
			Assert::AreEqual(1, int(parent_manager_.GetAllParentsFromStmt(2)->size()));
			Assert::AreEqual(2, int(parent_manager_.GetAllParentsFromStmt(4)->size()));
		}

		TEST_METHOD(TestGetAllParentTRelations) 
		{
			Assert::AreEqual(0, int(parent_manager_.GetAllParentTRelations()->size()));
			parent_manager_.SetParentT(1, 2);
			parent_manager_.SetParentT(2, 3);
			parent_manager_.SetParentT(1, 3);
			Assert::AreEqual(3, int(parent_manager_.GetAllParentTRelations()->size()));
		}
	};
}