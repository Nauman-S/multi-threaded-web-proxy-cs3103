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
		string base_dir = "../../Tests34/integration/SP_PKB/";
		SourceParser parser = SourceParser();

		shared_ptr<ReadPKBManager> read = ReadPKBManager::GetInstance();
		shared_ptr<WritePKBManager> write = WritePKBManager::GetInstance();
	public:
		
		TEST_METHOD(TestEntityPopulation)
		{
			string uses_source_file = base_dir + "entity_source.txt";
			shared_ptr<ProgramNode> root = this->parser.Parse(uses_source_file);
			DesignExtractor extractor;
			EntityExtractor entity_extractor;
			root->Extract(entity_extractor);
			extractor.AddConstants(uses_source_file);
			
			// Check all variables present
			shared_ptr<unordered_set<Variable>> present_vars = read->GetAllVariables();
			unordered_set<Variable> expected_vars = { "var1", "var2", "var3", "var4" };
			Assert::IsTrue(*present_vars == expected_vars);

			// Check all constants present
			shared_ptr<unordered_set<Constant>> present_consts = read->GetAllConstants();
			unordered_set<Constant> expected_consts = { 2, 5 };
			Assert::IsTrue(*present_consts == expected_consts);

			// Check all procedures present
			shared_ptr<unordered_set<Procedure>> present_procs = read->GetAllProcedures();
			unordered_set<Procedure> expected_procs = { "proc1", "proc2" };
			Assert::IsTrue(*present_procs == expected_procs);

			// Check for statement types: assign, print, read, call, if, while
			shared_ptr<unordered_set<StmtNum>> assign_stmts = read->GetStatementsByType(RefType::kAssignRef);
			unordered_set<StmtNum> expected_assign = { 1, 6, 7 };
			Assert::IsTrue(*assign_stmts == expected_assign);
			
			shared_ptr<unordered_set<StmtNum>> print_stmts = read->GetStatementsByType(RefType::kPrintRef);
			unordered_set<StmtNum> expected_print = { 2 };
			Assert::IsTrue(*print_stmts == expected_print);

			shared_ptr<unordered_set<StmtNum>> read_stmts = read->GetStatementsByType(RefType::kReadRef);
			unordered_set<StmtNum> expected_read = { 3 };
			Assert::IsTrue(*read_stmts == expected_read);

			shared_ptr<unordered_set<StmtNum>> call_stmts = read->GetStatementsByType(RefType::kCallRef);
			unordered_set<StmtNum> expected_call = { 5 };
			Assert::IsTrue(*call_stmts == expected_call);

			shared_ptr<unordered_set<StmtNum>> if_stmts = read->GetStatementsByType(RefType::kIfRef);
			unordered_set<StmtNum> expected_if = { 4 };
			Assert::IsTrue(*if_stmts == expected_if);

			//shared_ptr<unordered_set<StmtNum>> while_stmts = read->GetStatementsByType(RefType::kWhileRef);
			//unordered_set<StmtNum> expected_while = { 8 };
			//Assert::IsTrue(*while_stmts == expected_while);
		}

	};
}