#include <memory>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/manager/UsesManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestUsesManager)
	{
	private:
		UsesManager uses_manager_;
	public:
		TEST_METHOD(TestCheckSVUses) 
		{
			uses_manager_.SetUses(1, "x");
			Assert::IsTrue(uses_manager_.CheckUses(1, "x"));
			Assert::IsFalse(uses_manager_.CheckUses(1, "y"));
		}

		TEST_METHOD(TestCheckPVUses) 
		{
			uses_manager_.SetUses("proc1", "x");
			Assert::IsTrue(uses_manager_.CheckUses("proc1", "x"));
			Assert::IsFalse(uses_manager_.CheckUses("proc1", "y"));
		}

		TEST_METHOD(TestSetSVUses) 
		{
			uses_manager_.SetUses(1, "x");
			Assert::IsTrue(!uses_manager_.GetAllSVUses()->empty());
		};

		TEST_METHOD(TestSetPVUses) 
		{
			uses_manager_.SetUses("proc1", "x");
			Assert::IsTrue(!uses_manager_.GetAllPVUses()->empty());
		};

		TEST_METHOD(TestGetAllSVUses) 
		{
			uses_manager_.SetUses(1, "x");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> sv_uses = uses_manager_.GetAllSVUses();
			Assert::AreEqual(1, int(sv_uses->size()));
			uses_manager_.SetUses(1, "y");
			uses_manager_.SetUses(2, "z");
			sv_uses = uses_manager_.GetAllSVUses();
			Assert::AreEqual(3, int(sv_uses->size()));
		};

		TEST_METHOD(TestGetAllStatements) 
		{
			uses_manager_.SetUses(1, "x");
			std::shared_ptr<std::unordered_set<StmtNum>> stmts = uses_manager_.GetAllStatements();
			Assert::IsTrue(stmts->find(1) != stmts->end());
			Assert::AreEqual(1, int(stmts->size()));

			uses_manager_.SetUses(1, "y");
			uses_manager_.SetUses(2, "z");
			stmts = uses_manager_.GetAllStatements();
			Assert::IsTrue(stmts->find(1) != stmts->end());
			Assert::IsTrue(stmts->find(2) != stmts->end());
			Assert::AreEqual(2, int(stmts->size()));
		};

		TEST_METHOD(TestGetAllSVariables)
		{
			uses_manager_.SetUses(1, "x");
			std::shared_ptr<std::unordered_set<Variable>> vars = uses_manager_.GetAllSVariables();
			Assert::IsTrue(vars->find("x") != vars->end());
			Assert::AreEqual(1, int(vars->size()));

			uses_manager_.SetUses(1, "y");
			uses_manager_.SetUses(2, "z");
			vars = uses_manager_.GetAllSVariables();
			Assert::IsTrue(vars->find("x") != vars->end());
			Assert::IsTrue(vars->find("y") != vars->end());
			Assert::IsTrue(vars->find("z") != vars->end());
			Assert::AreEqual(3, int(vars->size()));
		};

		TEST_METHOD(TestGetAllPVUses) 
		{
			uses_manager_.SetUses("proc1", "x");
			std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> pv_uses = uses_manager_.GetAllPVUses();
			Assert::AreEqual(1, int(pv_uses->size()));
			uses_manager_.SetUses("proc1", "y");
			uses_manager_.SetUses("proc2", "z");
			pv_uses = uses_manager_.GetAllPVUses();
			Assert::AreEqual(3, int(pv_uses->size()));
		};

		TEST_METHOD(TestGetAllProcedures) 
		{
			uses_manager_.SetUses("proc1", "x");
			std::shared_ptr<std::unordered_set<Procedure>> procs = uses_manager_.GetAllProcedures();
			Assert::IsTrue(procs->find("proc1") != procs->end());
			Assert::AreEqual(1, int(procs->size()));

			uses_manager_.SetUses("proc1", "y");
			uses_manager_.SetUses("proc2", "z");
			procs = uses_manager_.GetAllProcedures();
			Assert::IsTrue(procs->find("proc1") != procs->end());
			Assert::IsTrue(procs->find("proc2") != procs->end());
			Assert::AreEqual(2, int(procs->size()));
		};

		TEST_METHOD(TestGetVarByStmtNum) 
		{
			uses_manager_.SetUses(1, "x");
			uses_manager_.SetUses(1, "y");
			std::shared_ptr<std::unordered_set<Variable>> vars = uses_manager_.GetVarByStmtNum(1);
			Assert::IsTrue(vars->find("x") != vars->end());
			Assert::IsTrue(vars->find("y") != vars->end());
			Assert::AreEqual(2, int(vars->size()));
		};

		TEST_METHOD(TestGetVarByProcName) 
		{
			uses_manager_.SetUses("proc1", "x");
			uses_manager_.SetUses("proc1", "y");
			std::shared_ptr<std::unordered_set<Variable>> vars = uses_manager_.GetVarByProcName("proc1");
			Assert::IsTrue(vars->find("x") != vars->end());
			Assert::IsTrue(vars->find("y") != vars->end());
			Assert::AreEqual(2, int(vars->size()));
		};

		TEST_METHOD(TestGetStmtNumByVar) 
		{
			uses_manager_.SetUses(1, "x");
			uses_manager_.SetUses(2, "x");
			std::shared_ptr<std::unordered_set<StmtNum>> stmts = uses_manager_.GetStmtNumByVar("x");
			Assert::IsTrue(stmts->find(1) != stmts->end());
			Assert::IsTrue(stmts->find(2) != stmts->end());
			Assert::AreEqual(2, int(stmts->size()));
		};

		TEST_METHOD(TestGetProcNameByVar) 
		{
			uses_manager_.SetUses("proc1", "x");
			uses_manager_.SetUses("proc2", "x");
			std::shared_ptr<std::unordered_set<Procedure>> procs = uses_manager_.GetProcNameByVar("x");
			Assert::IsTrue(procs->find("proc1") != procs->end());
			Assert::IsTrue(procs->find("proc2") != procs->end());
			Assert::AreEqual(2, int(procs->size()));
		};
	};
}