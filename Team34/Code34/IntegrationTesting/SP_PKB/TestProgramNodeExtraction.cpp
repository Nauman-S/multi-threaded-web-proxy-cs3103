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
#include "../SPA/SP/design_extractor/ParentsExtractor.h"
#include "../SPA/SP/design_extractor/FollowsExtractor.h"

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

		TEST_METHOD(TestUsesRelationPopulation) {
			UsesModifiesExtractor extractor;
			this->root->Extract(extractor);

			// Uses in procedure
			Assert::IsTrue(this->read->CheckUses("proc1", "var2"));
			Assert::IsTrue(this->read->CheckUses("proc1", "y"));

			// Uses on RHS of assignment
			Assert::IsTrue(this->read->CheckUses(1, "var2"));
			Assert::IsTrue(this->read->CheckUses(1, "var3"));
			Assert::IsFalse(this->read->CheckUses(1, "var"));

			// Uses on condition expression and children of while statement
			Assert::IsTrue(this->read->CheckUses(3, "x"));
			Assert::IsTrue(this->read->CheckUses(3, "var2"));

			// Uses on print statement
			Assert::IsTrue(this->read->CheckUses(5, "var3"));

			// Uses on procedure of call statement
			Assert::IsTrue(this->read->CheckUses(6, "CAPSVAR"));

			// Uses on condition expression of if stmt
			Assert::IsTrue(this->read->CheckUses(7, "y"));
			
			// Uses on indirect procedure call for statements and procedures
			Assert::IsTrue(this->read->CheckUses("proc2", "var2"));
			Assert::IsTrue(this->read->CheckUses(15, "var2"));

			// Uses on container statement for child statements
			Assert::IsTrue(this->read->CheckUses(18, "read"));
		}

		TEST_METHOD(TestModifiesRelationPopulation) {
			UsesModifiesExtractor extractor;
			this->root->Extract(extractor);

			// Modifies in procedure
			Assert::IsTrue(this->read->CheckModifies("proc1", "var"));

			// Modifies on LHS of assignment
			Assert::IsTrue(this->read->CheckModifies(1, "var"));
			Assert::IsFalse(this->read->CheckModifies(1, "var2"));

			// Modifies on children of if statement
			Assert::IsTrue(this->read->CheckModifies(7, "x"));

			// Modifies on read statement
			Assert::IsTrue(this->read->CheckModifies(9, "y"));

			// Modifies on procedure of call statement
			Assert::IsTrue(this->read->CheckModifies(6, "camelCase"));

			// Modifies on child statements of if stmt
			Assert::IsTrue(this->read->CheckModifies(7, "x"));
			
			// Modifies on indirect procedure call for statements and procedures
			Assert::IsTrue(this->read->CheckModifies("proc2", "print"));
			Assert::IsTrue(this->read->CheckModifies(15, "print"));
		}

		TEST_METHOD(TestParentsRelationPopulation) {
			ParentsExtractor extractor;
			this->root->Extract(extractor);

			// Parent and parent* relation for direct children of while stmts
			Assert::IsTrue(this->read->CheckParent(3, 4));
			Assert::IsTrue(this->read->CheckParent(3, 5));
			Assert::IsFalse(this->read->CheckParent(4, 3));

			Assert::IsTrue(this->read->CheckParentT(3, 4));
			Assert::IsTrue(this->read->CheckParentT(3, 5));

			// Parent relation for direct children of if stmts
			Assert::IsTrue(this->read->CheckParent(7, 8));
			Assert::IsTrue(this->read->CheckParent(7, 9));
			Assert::IsTrue(this->read->CheckParent(7, 10));

			Assert::IsTrue(this->read->CheckParentT(7, 8));
			Assert::IsTrue(this->read->CheckParentT(7, 9));
			Assert::IsTrue(this->read->CheckParentT(7, 10));
			
			// Parent relation for if nested in while
			Assert::IsTrue(this->read->CheckParent(12, 15));
			Assert::IsFalse(this->read->CheckParent(12, 16));
			Assert::IsTrue(this->read->CheckParentT(12, 16));
			Assert::IsTrue(this->read->CheckParentT(12, 17));

			// Parent relation for while nested in if
			Assert::IsTrue(this->read->CheckParent(18, 20));
			Assert::IsTrue(this->read->CheckParentT(18, 21));
		}

		TEST_METHOD(TestFollowsRelationPopulation) {
			FollowsExtractor extractor;
			this->root->Extract(extractor);

			// Follows relation for stmts in single procedure
			Assert::IsTrue(this->read->CheckFollows(1, 2));
			Assert::IsTrue(this->read->CheckFollows(2, 3));
			Assert::IsFalse(this->read->CheckFollows(3, 4));

			Assert::IsTrue(this->read->CheckFollowsT(1, 3));
			Assert::IsFalse(this->read->CheckFollowsT(1, 5));
			Assert::IsTrue(this->read->CheckFollowsT(2, 7));

			// Follows relation within while loop
			Assert::IsTrue(this->read->CheckFollows(4, 5));
			Assert::IsFalse(this->read->CheckFollows(5, 6));

			// Follows relation within if loop
			Assert::IsTrue(this->read->CheckFollows(8, 9));
			Assert::IsFalse(this->read->CheckFollows(9, 10));
		}
	};
}