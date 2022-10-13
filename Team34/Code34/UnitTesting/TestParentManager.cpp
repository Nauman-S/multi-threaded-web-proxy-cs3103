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
			std::shared_ptr<std::unordered_set<StmtNum>> children_1 = parent_manager_.GetChildrenFromStmt(1);
			Assert::IsTrue(children_1->find(2) != children_1->end());
			Assert::IsTrue(children_1->find(3) != children_1->end());
			Assert::AreEqual(2, int(children_1->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> children_2 = parent_manager_.GetChildrenFromStmt(2);
			Assert::IsTrue(children_2->find(4) != children_2->end());
			Assert::AreEqual(1, int(children_2->size()));
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
			std::shared_ptr<std::unordered_set<StmtNum>> all_parents = parent_manager_.GetAllParents();
			Assert::IsTrue(all_parents->find(1) != all_parents->end());
			Assert::IsTrue(all_parents->find(2) != all_parents->end());
			Assert::AreEqual(2, int(all_parents->size()));
		}

		TEST_METHOD(TestGetAllChildren) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);
			std::shared_ptr<std::unordered_set<StmtNum>> all_children = parent_manager_.GetAllChildren();
			Assert::IsTrue(all_children->find(2) != all_children->end());
			Assert::IsTrue(all_children->find(3) != all_children->end());
			Assert::IsTrue(all_children->find(4) != all_children->end());
			Assert::AreEqual(3, int(all_children->size()));
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

			std::shared_ptr<std::unordered_set<StmtNum>> children_1 = parent_manager_.GetChildrenFromStmt(1);
			Assert::IsTrue(children_1->find(2) != children_1->end());
			Assert::IsTrue(children_1->find(3) != children_1->end());
			Assert::AreEqual(2, int(children_1->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> children_2 = parent_manager_.GetChildrenFromStmt(2);
			Assert::IsTrue(children_2->find(4) != children_2->end());
			Assert::AreEqual(1, int(children_2->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> children_3 = parent_manager_.GetChildrenFromStmt(3);
			Assert::AreEqual(0, int(children_3->size()));
		}

		TEST_METHOD(TestGetAllParentsFromStmt) 
		{
			parent_manager_.SetParent(1, 2);
			parent_manager_.SetParent(1, 3);
			parent_manager_.SetParent(2, 4);

			std::shared_ptr<std::unordered_set<StmtNum>> parent_1 = parent_manager_.GetAllParentsFromStmt(1);
			Assert::AreEqual(0, int(parent_1->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> parent_2 = parent_manager_.GetAllParentsFromStmt(2);
			Assert::IsTrue(parent_2->find(1) != parent_2->end());
			Assert::AreEqual(1, int(parent_2->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> parent_4 = parent_manager_.GetAllParentsFromStmt(4);
			Assert::IsTrue(parent_4->find(1) != parent_4->end());
			Assert::IsTrue(parent_4->find(2) != parent_4->end());
			Assert::AreEqual(2, int(parent_4->size()));
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