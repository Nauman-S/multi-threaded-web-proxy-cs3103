#include <memory>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/manager/StatementManager.h"
#include "../SPA/Utils/type/RefType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestStatementManager)
	{
	private:
		StatementManager statement_manager_;
	public:
		TEST_METHOD(TestAddStatement)
		{
			statement_manager_.AddStatement(1, RefType::kAssignRef);
			statement_manager_.AddStatement(1, RefType::kCallRef);

			std::shared_ptr<std::unordered_set<StmtNum>> assign_stmts = statement_manager_.GetStatementsByType(RefType::kAssignRef);
			Assert::IsTrue(assign_stmts->find(1) != assign_stmts->end());
			Assert::AreEqual(1, int(assign_stmts->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> call_stmts = statement_manager_.GetStatementsByType(RefType::kCallRef);
			Assert::AreEqual(0, int(call_stmts->size()));

			std::shared_ptr<std::unordered_set<StmtNum>> all_stmts = statement_manager_.GetAllStatements();
			Assert::IsTrue(all_stmts->find(1) != all_stmts->end());
			Assert::AreEqual(1, int(all_stmts->size()));
		};

		TEST_METHOD(TestAddCallsStatement)
		{
			std::shared_ptr<std::unordered_set<StmtNum>> call_stmts = statement_manager_.GetCallsStatementFromProcedure("test");
			Assert::AreEqual(0, int(call_stmts->size()));

			statement_manager_.AddCallsStatement("test", 1);
			call_stmts = statement_manager_.GetCallsStatementFromProcedure("test");
			Assert::IsTrue(call_stmts->find(1) != call_stmts->end());
			Assert::AreEqual(1, int(call_stmts->size()));

			statement_manager_.AddCallsStatement("test", 1);
			call_stmts = statement_manager_.GetCallsStatementFromProcedure("test");
			Assert::IsTrue(call_stmts->find(1) != call_stmts->end());
			Assert::AreEqual(1, int(call_stmts->size()));
		}

		TEST_METHOD(TestAddPrintStatement)
		{
			std::shared_ptr<std::unordered_set<StmtNum>> print_stmts = statement_manager_.GetPrintStatementFromVariable("test");
			Assert::AreEqual(0, int(print_stmts->size()));

			statement_manager_.AddPrintStatement("test", 1);
			print_stmts = statement_manager_.GetPrintStatementFromVariable("test");
			Assert::IsTrue(print_stmts->find(1) != print_stmts->end());
			Assert::AreEqual(1, int(print_stmts->size()));

			statement_manager_.AddPrintStatement("test", 1);
			print_stmts = statement_manager_.GetPrintStatementFromVariable("test");
			Assert::IsTrue(print_stmts->find(1) != print_stmts->end());
			Assert::AreEqual(1, int(print_stmts->size()));
		}

		TEST_METHOD(TestAddReadStatement)
		{
			std::shared_ptr<std::unordered_set<StmtNum>> read_stmts = statement_manager_.GetReadStatementFromVariable("test");
			Assert::AreEqual(0, int(read_stmts->size()));
			
			statement_manager_.AddReadStatement("test", 1);
			read_stmts = statement_manager_.GetReadStatementFromVariable("test");
			Assert::IsTrue(read_stmts->find(1) != read_stmts->end());
			Assert::AreEqual(1, int(read_stmts->size()));

			statement_manager_.AddReadStatement("test", 1);
			read_stmts = statement_manager_.GetReadStatementFromVariable("test");
			Assert::IsTrue(read_stmts->find(1) != read_stmts->end());
			Assert::AreEqual(1, int(read_stmts->size()));
		}

		TEST_METHOD(TestGetStatementType)
		{
			statement_manager_.AddStatement(1, RefType::kAssignRef);
			Assert::IsTrue(*statement_manager_.GetStatementType(1) == RefType::kAssignRef);
			statement_manager_.AddStatement(2, RefType::kCallRef);
			Assert::IsTrue(*statement_manager_.GetStatementType(2) == RefType::kCallRef);
			statement_manager_.AddStatement(3, RefType::kPrintRef);
			Assert::IsTrue(*statement_manager_.GetStatementType(3) == RefType::kPrintRef);
		};

		TEST_METHOD(TestGetStatementsByType)
		{
			statement_manager_.AddStatement(1, RefType::kAssignRef);
			std::shared_ptr<std::unordered_set<StmtNum>> assign_stmts = statement_manager_.GetStatementsByType(RefType::kAssignRef);
			Assert::IsTrue(assign_stmts->find(1) != assign_stmts->end());
			Assert::AreEqual(1, int(assign_stmts->size()));

			statement_manager_.AddStatement(2, RefType::kAssignRef);
			assign_stmts = statement_manager_.GetStatementsByType(RefType::kAssignRef);
			Assert::IsTrue(assign_stmts->find(1) != assign_stmts->end());
			Assert::IsTrue(assign_stmts->find(2) != assign_stmts->end());
			Assert::AreEqual(2, int(assign_stmts->size()));
		};

		TEST_METHOD(TestGetAllStatements)
		{
			Assert::AreEqual(0, int(statement_manager_.GetAllStatements()->size()));
			statement_manager_.AddStatement(1, RefType::kAssignRef);
			statement_manager_.AddStatement(2, RefType::kCallRef);
			statement_manager_.AddStatement(3, RefType::kPrintRef);

			std::shared_ptr<std::unordered_set<StmtNum>> all_stmts = statement_manager_.GetAllStatements();
			Assert::IsTrue(all_stmts->find(1) != all_stmts->end());
			Assert::IsTrue(all_stmts->find(2) != all_stmts->end());
			Assert::IsTrue(all_stmts->find(3) != all_stmts->end());
			Assert::AreEqual(3, int(all_stmts->size()));
		};

		TEST_METHOD(TestGetCallsStatementFromProcedure)
		{
			std::shared_ptr<std::unordered_set<StmtNum>> call_stmts = statement_manager_.GetCallsStatementFromProcedure("test");
			Assert::AreEqual(0, int(call_stmts->size()));

			statement_manager_.AddCallsStatement("test", 1);
			call_stmts = statement_manager_.GetCallsStatementFromProcedure("test");
			Assert::IsTrue(call_stmts->find(1) != call_stmts->end());
			Assert::AreEqual(1, int(call_stmts->size()));

			statement_manager_.AddCallsStatement("test", 2);
			call_stmts = statement_manager_.GetCallsStatementFromProcedure("test");
			Assert::IsTrue(call_stmts->find(1) != call_stmts->end());
			Assert::IsTrue(call_stmts->find(2) != call_stmts->end());
			Assert::AreEqual(2, int(call_stmts->size()));
		};

		TEST_METHOD(TestGetPrintStatementFromProcedure)
		{
			std::shared_ptr<std::unordered_set<StmtNum>> print_stmts = statement_manager_.GetPrintStatementFromVariable("test");
			Assert::AreEqual(0, int(print_stmts->size()));

			statement_manager_.AddPrintStatement("test", 1);
			print_stmts = statement_manager_.GetPrintStatementFromVariable("test");
			Assert::IsTrue(print_stmts->find(1) != print_stmts->end());
			Assert::AreEqual(1, int(print_stmts->size()));

			statement_manager_.AddPrintStatement("test", 2);
			print_stmts = statement_manager_.GetPrintStatementFromVariable("test");
			Assert::IsTrue(print_stmts->find(1) != print_stmts->end());
			Assert::IsTrue(print_stmts->find(2) != print_stmts->end());
			Assert::AreEqual(2, int(print_stmts->size()));
		};

		TEST_METHOD(TestGetReadStatementFromProcedure)
		{
			std::shared_ptr<std::unordered_set<StmtNum>> read_stmts = statement_manager_.GetReadStatementFromVariable("test");
			Assert::AreEqual(0, int(read_stmts->size()));

			statement_manager_.AddReadStatement("test", 1);
			read_stmts = statement_manager_.GetReadStatementFromVariable("test");
			Assert::IsTrue(read_stmts->find(1) != read_stmts->end());
			Assert::AreEqual(1, int(read_stmts->size()));

			statement_manager_.AddReadStatement("test", 2);
			read_stmts = statement_manager_.GetReadStatementFromVariable("test");
			Assert::IsTrue(read_stmts->find(1) != read_stmts->end());
			Assert::IsTrue(read_stmts->find(2) != read_stmts->end());
			Assert::AreEqual(2, int(read_stmts->size()));
		};

		TEST_METHOD(TestGetCallsProcedureFromStatement)
		{
			std::shared_ptr<Procedure> empty_ptr = std::make_shared<Procedure>();
			Assert::AreEqual(*empty_ptr, *statement_manager_.GetCallsProcedureFromStatement(1));
			statement_manager_.AddCallsStatement("test", 1);
			Assert::AreEqual(Procedure("test"), *statement_manager_.GetCallsProcedureFromStatement(1));
			statement_manager_.AddCallsStatement("test2", 2);
			Assert::AreEqual(Procedure("test2"), *statement_manager_.GetCallsProcedureFromStatement(2));
		}

		TEST_METHOD(TestGetPrintVariableFromStatement)
		{
			std::shared_ptr<Variable> empty_ptr = std::make_shared<Variable>();
			Assert::AreEqual(*empty_ptr, *statement_manager_.GetPrintVariableFromStatement(1));
			statement_manager_.AddPrintStatement("test_print_var", 1);
			Assert::AreEqual(Variable("test_print_var"), *statement_manager_.GetPrintVariableFromStatement(1));
			statement_manager_.AddPrintStatement("test_print_var2", 2);
			Assert::AreEqual(Variable("test_print_var2"), *statement_manager_.GetPrintVariableFromStatement(2));
		}

		TEST_METHOD(TestGetReadVariableFromStatement)
		{
			std::shared_ptr<Variable> empty_ptr = std::make_shared<Variable>();
			Assert::AreEqual(*empty_ptr, *statement_manager_.GetReadVariableFromStatement(1));
			statement_manager_.AddReadStatement("test_read_var", 1);
			Assert::AreEqual(Variable("test_read_var"), *statement_manager_.GetReadVariableFromStatement(1));
			statement_manager_.AddReadStatement("test_read_var2", 2);
			Assert::AreEqual(Variable("test_read_var2"), *statement_manager_.GetReadVariableFromStatement(2));
		}
	};
}