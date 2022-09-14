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
		TEST_METHOD(TestSetSVUses) {
			uses_manager_.SetUses(1, "x");
			Assert::IsTrue(!uses_manager_.GetAllSVUses()->empty());
		};

		TEST_METHOD(TestSetPVUses) {
			uses_manager_.SetUses("proc1", "x");
			Assert::IsTrue(!uses_manager_.GetAllPVUses()->empty());
		};

		TEST_METHOD(TestCheckUses) {
			uses_manager_.SetUses(1, "x");
			uses_manager_.SetUses("proc1", "x");
			Assert::IsTrue(uses_manager_.CheckUses("proc1", "x"));
			Assert::IsTrue(uses_manager_.CheckUses(1, "x"));
			Assert::IsFalse (uses_manager_.CheckUses("proc1", "y"));
			Assert::IsFalse (uses_manager_.CheckUses(1, "y"));
		}

		TEST_METHOD(TestGetVarByStmtNum) {
			uses_manager_.SetUses(1, "x");
			uses_manager_.SetUses(1, "y");
			std::shared_ptr<std::unordered_set<Variable>> vars = uses_manager_.GetVarByStmtNum(1);
			// vars should contain ["x", "y"]
			Assert::AreEqual(int(vars->size()), 2);
		};

		TEST_METHOD(TestGetProcByStmtNum) {
			uses_manager_.SetUses("proc1", "x");
			uses_manager_.SetUses("proc1", "y");
			std::shared_ptr<std::unordered_set<Variable>> vars = uses_manager_.GetVarByProcName("proc1");
			// vars should contain ["x", "y"]
			Assert::AreEqual(int(vars->size()), 2);
		};

		TEST_METHOD(TestGetStmtNumByVar) {
			uses_manager_.SetUses(1, "x");
			uses_manager_.SetUses(2, "x");
			std::shared_ptr<std::unordered_set<StmtNum>> stmts = uses_manager_.GetStmtNumByVar("x");
			// stmts should contain [1, 2]
			Assert::AreEqual(int(stmts->size()), 2);
		};

		TEST_METHOD(TestGetProcNameByVar) {
			uses_manager_.SetUses("proc1", "x");
			uses_manager_.SetUses("proc2", "x");
			std::shared_ptr<std::unordered_set<Procedure>> procs = uses_manager_.GetProcNameByVar("x");
			// procs should contain ["proc1", "proc2"]
			Assert::AreEqual(int(procs->size()), 2);
		};

		TEST_METHOD(TestGetAllPVUses) {
			uses_manager_.SetUses("proc1", "x");
			uses_manager_.SetUses("proc1", "y");
			uses_manager_.SetUses("proc2", "z");
			std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> pv_uses = uses_manager_.GetAllPVUses();
			Assert::AreEqual(int(pv_uses->size()), 3);
		}

		TEST_METHOD(TestGetAllProcedures) {
			uses_manager_.SetUses("proc1", "x");
			uses_manager_.SetUses("proc1", "y");
			uses_manager_.SetUses("proc2", "z");
			std::shared_ptr<std::unordered_set<Procedure>> procs = uses_manager_.GetAllProcedures();
			// procs should contain ["proc1", "proc2"]
			Assert::AreEqual(int(procs->size()), 2);
		}

		TEST_METHOD(TestGetAllSVUses) {
			uses_manager_.SetUses(1, "x");
			uses_manager_.SetUses(1, "y");
			uses_manager_.SetUses(2, "z");
			std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> sv_uses = uses_manager_.GetAllSVUses();
			Assert::AreEqual(int(sv_uses->size()), 3);
		}

		TEST_METHOD(TestGetAllStatements) {
			uses_manager_.SetUses(1, "x");
			uses_manager_.SetUses(1, "y");
			uses_manager_.SetUses(2, "z");
			std::shared_ptr<std::unordered_set<StmtNum>> stmts = uses_manager_.GetAllStatements();
			// stmts should contain [1, 2]
			Assert::AreEqual(int(stmts->size()), 2);
		}
	};
}