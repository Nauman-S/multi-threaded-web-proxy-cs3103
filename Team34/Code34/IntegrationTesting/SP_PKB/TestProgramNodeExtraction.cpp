#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>
#include <string>
#include <iostream>

#include "../SPA/PKB/ReadPKBManager.h"
#include "../SPA/PKB/WritePKBManager.h"

#include "../SPA/SP/SourceParser.h"
#include "../SPA/SP/SourceParser.h"

#include "../SPA/SP/design_extractor/EntityExtractor.h"
#include "../SPA/SP/design_extractor/DesignExtractor.h"
#include "../SPA/SP/design_extractor/UsesModifiesExtractor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting
{		
	TEST_CLASS(TestProgramNodeExtraction)
	{
	private:
		string test_file = "../../Tests34/integration_tests/SP_PKB/design_extractor_test_source.txt";
		shared_ptr<ProgramNode> root;

		shared_ptr<ReadPKBManager> read;
		shared_ptr<WritePKBManager> write;
	public:
		
		TestProgramNodeExtraction() {
			SourceParser parser = SourceParser();
			this->root = parser.Parse(this->test_file);
			this->read = ReadPKBManager::GetInstance();
			this->write = WritePKBManager::GetInstance();
		}
		TEST_METHOD(TestEntityPopulation)
		{
			DesignExtractor extractor;
			EntityExtractor entity_extractor;
			this->root->Extract(entity_extractor);
			extractor.AddConstants(this->test_file);
			
			// Check all variables present
			shared_ptr<unordered_set<Variable>> present_vars = read->GetAllVariables();
			unordered_set<Variable> expected_vars = { "var", "x", "var2", "var3", "y",
			"camelCase", "CAPSVAR", "read", "call", "print" };
			Assert::IsTrue(*present_vars == expected_vars);

			// Check all constants present
			shared_ptr<unordered_set<Constant>> present_consts = read->GetAllConstants();
			unordered_set<Constant> expected_consts = { 0, 1, 2, 3, 5 };
			Assert::IsTrue(*present_consts == expected_consts);

			// Check all procedures present
			shared_ptr<unordered_set<Procedure>> present_procs = read->GetAllProcedures();
			unordered_set<Procedure> expected_procs = { "proc1", "proc2", "procedure" };
			Assert::IsTrue(*present_procs == expected_procs);

			// Check for statement types: assign, print, read, call, if, while
			shared_ptr<unordered_set<StmtNum>> assign_stmts = read->GetStatementsByType(RefType::kAssignRef);
			unordered_set<StmtNum> expected_assign = { 1, 2, 10, 11, 13, 14, 16, 19, 21, 22 };
			Assert::IsTrue(*assign_stmts == expected_assign);
			
			shared_ptr<unordered_set<StmtNum>> print_stmts = read->GetStatementsByType(RefType::kPrintRef);
			unordered_set<StmtNum> expected_print = { 4, 5 };
			Assert::IsTrue(*print_stmts == expected_print);

			shared_ptr<unordered_set<StmtNum>> read_stmts = read->GetStatementsByType(RefType::kReadRef);
			unordered_set<StmtNum> expected_read = { 8, 9 };
			Assert::IsTrue(*read_stmts == expected_read);

			shared_ptr<unordered_set<StmtNum>> call_stmts = read->GetStatementsByType(RefType::kCallRef);
			unordered_set<StmtNum> expected_call = { 6, 17 };
			Assert::IsTrue(*call_stmts == expected_call);

			shared_ptr<unordered_set<StmtNum>> if_stmts = read->GetStatementsByType(RefType::kIfRef);
			unordered_set<StmtNum> expected_if = { 7, 15, 18 };
			Assert::IsTrue(*if_stmts == expected_if);

			shared_ptr<unordered_set<StmtNum>> while_stmts = read->GetStatementsByType(RefType::kWhileRef);
			unordered_set<StmtNum> expected_while = { 3, 12, 20 };
			Assert::IsTrue(*while_stmts == expected_while);
		}
	};
}