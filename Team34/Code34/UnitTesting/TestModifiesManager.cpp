#include <memory>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/manager/ModifiesManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestModifiesManager)
	{
	private:
		ModifiesManager modifies_manager_;
	public:
		TEST_METHOD(TestCheckSVModifies)
		{
			modifies_manager_.SetModifies(1, "x");
			Assert::IsTrue(modifies_manager_.CheckModifies(1, "x"));
			Assert::IsFalse(modifies_manager_.CheckModifies(1, "y"));
		};

		TEST_METHOD(TestCheckPVModifies) 
		{
			modifies_manager_.SetModifies("proc1", "x");
			Assert::IsTrue(modifies_manager_.CheckModifies("proc1", "x"));
			Assert::IsFalse(modifies_manager_.CheckModifies("proc1", "y"));
		};

		TEST_METHOD(TestSetSVModifies) 
		{
			modifies_manager_.SetModifies(1, "x");
			Assert::IsTrue(!modifies_manager_.GetAllSVModifies()->empty());
		};

		TEST_METHOD(TestSetPVModifies) 
		{
			modifies_manager_.SetModifies("proc1", "x");
			Assert::IsTrue(!modifies_manager_.GetAllPVModifies()->empty());
		};

		TEST_METHOD(TestGetAllSVModifies) 
		{
			modifies_manager_.SetModifies(1, "x");
			modifies_manager_.SetModifies(2, "y");
			modifies_manager_.SetModifies(3, "z");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> all_pairs = modifies_manager_.GetAllSVModifies();
			Assert::AreEqual(3, int(all_pairs->size()));
		};

		TEST_METHOD(TestGetAllStatements)
		{
			modifies_manager_.SetModifies(1, "x");
			modifies_manager_.SetModifies(2, "y");
			modifies_manager_.SetModifies(3, "z");
			std::shared_ptr<std::unordered_set<StmtNum>> stmts = modifies_manager_.GetAllStatements();
			Assert::IsTrue(stmts->find(1) != stmts->end());
			Assert::IsTrue(stmts->find(2) != stmts->end());
			Assert::IsTrue(stmts->find(3) != stmts->end());
			Assert::AreEqual(3, int(stmts->size()));
		};

		TEST_METHOD(TestGetAllSVariables)
		{
			modifies_manager_.SetModifies(1, "x");
			modifies_manager_.SetModifies(2, "y");
			modifies_manager_.SetModifies(3, "z");
			std::shared_ptr<std::unordered_set<Variable>> vars = modifies_manager_.GetAllSVariables();
			Assert::IsTrue(vars->find("x") != vars->end());
			Assert::IsTrue(vars->find("y") != vars->end());
			Assert::IsTrue(vars->find("z") != vars->end());
			Assert::AreEqual(3, int(vars->size()));

			modifies_manager_.SetModifies(4, "z");
			vars = modifies_manager_.GetAllSVariables();
			Assert::AreEqual(3, int(vars->size()));
		};

		TEST_METHOD(TestGetAllPVModifies) 
		{
			modifies_manager_.SetModifies("proc1", "x");
			modifies_manager_.SetModifies("proc1", "y");
			modifies_manager_.SetModifies("proc2", "z");
			std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> all_pairs = modifies_manager_.GetAllPVModifies();
			Assert::AreEqual(3, int(all_pairs->size()));
		};

		TEST_METHOD(TestGetAllProcedures) 
		{
			modifies_manager_.SetModifies("proc1", "x");
			modifies_manager_.SetModifies("proc1", "y");
			modifies_manager_.SetModifies("proc2", "z");
			std::shared_ptr<std::unordered_set<Procedure>> procs = modifies_manager_.GetAllProcedures();
			Assert::IsTrue(procs->find("proc1") != procs->end());
			Assert::IsTrue(procs->find("proc2") != procs->end());
			Assert::AreEqual(2, int(procs->size()));
		}

		TEST_METHOD(TestGetVarByStmtNum) {
			modifies_manager_.SetModifies(1, "x");
			std::shared_ptr<std::unordered_set<Variable>> var_1 = modifies_manager_.GetVarByStmtNum(1);
			Assert::IsTrue(var_1->find("x") != var_1->end());

			std::shared_ptr<std::unordered_set<Variable>> var_2 = modifies_manager_.GetVarByStmtNum(2);
			Assert::AreEqual(0, int(var_2->size()));
		};

		TEST_METHOD(TestGetVarByProcName) 
		{
			modifies_manager_.SetModifies("proc1", "x");
			std::shared_ptr<std::unordered_set<Variable>> vars = modifies_manager_.GetVarByProcName("proc1");
			Assert::IsTrue(vars->find("x") != vars->end());
			Assert::AreEqual(1, int(vars->size()));

			modifies_manager_.SetModifies("proc1", "y");
			vars = modifies_manager_.GetVarByProcName("proc1");
			Assert::IsTrue(vars->find("x") != vars->end());
			Assert::IsTrue(vars->find("y") != vars->end());
			Assert::AreEqual(2, int(vars->size()));
		};

		TEST_METHOD(TestGetStmtNumByVar) 
		{
			modifies_manager_.SetModifies(1, "x");
			std::shared_ptr<std::unordered_set<StmtNum>> stmts = modifies_manager_.GetStmtNumByVar("x");
			Assert::IsTrue(stmts->find(1) != stmts->end());
			Assert::AreEqual(1, int(stmts->size()));

			modifies_manager_.SetModifies(2, "x");
			stmts = modifies_manager_.GetStmtNumByVar("x");
			Assert::IsTrue(stmts->find(1) != stmts->end());
			Assert::IsTrue(stmts->find(2) != stmts->end());
			Assert::AreEqual(2, int(stmts->size()));
		};

		TEST_METHOD(TestGetProcNameByVar) 
		{
			modifies_manager_.SetModifies("proc1", "x");
			std::shared_ptr<std::unordered_set<Procedure>> procs = modifies_manager_.GetProcNameByVar("x");
			Assert::AreEqual(1, int(procs->size()));
			modifies_manager_.SetModifies("proc2", "x");
			procs = modifies_manager_.GetProcNameByVar("x");
			Assert::AreEqual(2, int(procs->size()));
		};

		TEST_METHOD(TestClearModifiesStore)
		{
			modifies_manager_.SetModifies("proc1", "x");
			modifies_manager_.SetModifies(1, "x");
			Assert::AreEqual(1, int(modifies_manager_.GetProcNameByVar("x")->size()));
			Assert::AreEqual(1, int(modifies_manager_.GetVarByProcName("proc1")->size()));
			Assert::AreEqual(1, int(modifies_manager_.GetStmtNumByVar("x")->size()));
			Assert::AreEqual(1, int(modifies_manager_.GetVarByStmtNum(1)->size()));

			modifies_manager_.Clear();
			Assert::AreEqual(0, int(modifies_manager_.GetProcNameByVar("x")->size()));
			Assert::AreEqual(0, int(modifies_manager_.GetVarByProcName("proc1")->size()));
			Assert::AreEqual(0, int(modifies_manager_.GetStmtNumByVar("x")->size()));
			Assert::AreEqual(0, int(modifies_manager_.GetVarByStmtNum(1)->size()));
		}
	};
}