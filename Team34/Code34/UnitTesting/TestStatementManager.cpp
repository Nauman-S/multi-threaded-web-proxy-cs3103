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
			Assert::AreEqual(1, int(statement_manager_.GetStatementsByType(RefType::kAssignRef)->size()));
			Assert::AreEqual(0, int(statement_manager_.GetStatementsByType(RefType::kCallRef)->size()));
			Assert::AreEqual(1, int(statement_manager_.GetAllStatements()->size()));
		};

		TEST_METHOD(TestAddCallsStatement)
		{
			Assert::AreEqual(0, int(statement_manager_.GetCallsStatementFromProcedure("test")->size()));
			statement_manager_.AddCallsStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetCallsStatementFromProcedure("test")->size()));
			statement_manager_.AddCallsStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetCallsStatementFromProcedure("test")->size()));
		}

		TEST_METHOD(TestAddPrintStatement)
		{
			Assert::AreEqual(0, int(statement_manager_.GetPrintStatementFromVariable("test")->size()));
			statement_manager_.AddPrintStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetPrintStatementFromVariable("test")->size()));
			statement_manager_.AddPrintStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetPrintStatementFromVariable("test")->size()));
		}

		TEST_METHOD(TestAddReadStatement)
		{
			Assert::AreEqual(0, int(statement_manager_.GetReadStatementFromVariable("test")->size()));
			statement_manager_.AddReadStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetReadStatementFromVariable("test")->size()));
			statement_manager_.AddReadStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetReadStatementFromVariable("test")->size()));
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
			Assert::AreEqual(1, int(statement_manager_.GetStatementsByType(RefType::kAssignRef)->size()));
			statement_manager_.AddStatement(2, RefType::kAssignRef);
			Assert::AreEqual(2, int(statement_manager_.GetStatementsByType(RefType::kAssignRef)->size()));
		};

		TEST_METHOD(TestGetAllStatements)
		{
			Assert::AreEqual(0, int(statement_manager_.GetAllStatements()->size()));
			statement_manager_.AddStatement(1, RefType::kAssignRef);
			statement_manager_.AddStatement(2, RefType::kCallRef);
			statement_manager_.AddStatement(3, RefType::kPrintRef);
			Assert::AreEqual(3, int(statement_manager_.GetAllStatements()->size()));
		};

		TEST_METHOD(TestGetCallsStatementFromProcedure)
		{
			Assert::AreEqual(0, int(statement_manager_.GetCallsStatementFromProcedure("test")->size()));
			statement_manager_.AddCallsStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetCallsStatementFromProcedure("test")->size()));
			statement_manager_.AddCallsStatement("test", 2);
			Assert::AreEqual(2, int(statement_manager_.GetCallsStatementFromProcedure("test")->size()));
		};

		TEST_METHOD(TestGetPrintStatementFromProcedure)
		{
			Assert::AreEqual(0, int(statement_manager_.GetPrintStatementFromVariable("test")->size()));
			statement_manager_.AddPrintStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetPrintStatementFromVariable("test")->size()));
			statement_manager_.AddPrintStatement("test", 2);
			Assert::AreEqual(2, int(statement_manager_.GetPrintStatementFromVariable("test")->size()));
		};

		TEST_METHOD(TestGetReadStatementFromProcedure)
		{
			Assert::AreEqual(0, int(statement_manager_.GetReadStatementFromVariable("test")->size()));
			statement_manager_.AddReadStatement("test", 1);
			Assert::AreEqual(1, int(statement_manager_.GetReadStatementFromVariable("test")->size()));
			statement_manager_.AddReadStatement("test", 2);
			Assert::AreEqual(2, int(statement_manager_.GetReadStatementFromVariable("test")->size()));
		};
	};
}