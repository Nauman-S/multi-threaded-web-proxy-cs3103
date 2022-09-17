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
			Assert::AreEqual(1, int(statement_manager_.GetStatementsByType(RefType::kAssignRef)->size()));
			Assert::AreEqual(0, int(statement_manager_.GetStatementsByType(RefType::kCallRef)->size()));
		};

		TEST_METHOD(TestIsStatement)
		{
			statement_manager_.AddStatement(1, RefType::kAssignRef);
			Assert::IsTrue(statement_manager_.IsStatement(1));
			Assert::IsFalse(statement_manager_.IsStatement(2));
		};

		TEST_METHOD(TestGetStatementType)
		{
			statement_manager_.AddStatement(1, RefType::kAssignRef);
			Assert::IsTrue(statement_manager_.GetStatementType(1) == RefType::kAssignRef);
			statement_manager_.AddStatement(2, RefType::kCallRef);
			Assert::IsTrue(statement_manager_.GetStatementType(2) == RefType::kCallRef);
			statement_manager_.AddStatement(3, RefType::kPrintRef);
			Assert::IsTrue(statement_manager_.GetStatementType(3) == RefType::kPrintRef);
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
	};
}