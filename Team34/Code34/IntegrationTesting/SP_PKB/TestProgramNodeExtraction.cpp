#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>
#include <string>
#include <iostream>

#include "../SPA/PKB/ReadPKBManager.h"
#include "../SPA/PKB/WritePKBManager.h"

#include "../SPA/SP/SourceParser.h"
#include "../SPA/SP/tokenizer/SourceLexer.h"

#include "../SPA/SP/design_extractor/EntityExtractor.h"
#include "../SPA/SP/design_extractor/UsesModifiesExtractor.h"
#include "../SPA/SP/design_extractor/ParentsExtractor.h"
#include "../SPA/SP/design_extractor/FollowsExtractor.h"
#include "../SPA/SP/design_extractor/CallsExtractor.h"
#include "../SPA/SP/design_extractor/NextExtractor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting
{		
    TEST_CLASS(TestProgramNodeExtraction)
    {
    private:
        string base_dir = "../../Tests34/integration_tests/SP_PKB/design_extractor/";
        shared_ptr<ProgramNode> common_root;

        shared_ptr<ReadPKBManager> read;
        shared_ptr<WritePKBManager> write;
    public:
        
        TestProgramNodeExtraction() {
            SourceParser parser = SourceParser();
            SourceLexer lexer = SourceLexer(this->base_dir + "design_extractor_test_source.txt");
            parser.SetTokens(lexer.GetAllTokens());
            this->common_root = parser.Parse();
            this->read = ReadPKBManager::GetInstance();
            this->write = WritePKBManager::GetInstance();
        }

        TEST_METHOD(TestEntityPopulation)
        {
            this->write->ResetPKB();
            EntityExtractor entity_extractor(this->write);
            this->common_root->Extract(entity_extractor);
            
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

            // Check call, print and read variables
            shared_ptr<unordered_set<StmtNum>> calls_with_var = read->GetCallsStatementFromProcedure("proc2");
            unordered_set<StmtNum> expected_stmt_for_calls = { 6 };
            Assert::IsTrue(*calls_with_var == expected_stmt_for_calls);
            calls_with_var = read->GetCallsStatementFromProcedure("procedure");
            expected_stmt_for_calls = { 17 };
            Assert::IsTrue(*calls_with_var == expected_stmt_for_calls);

            shared_ptr<unordered_set<StmtNum>> print_with_var = read->GetPrintStatementFromVariable("var2");
            unordered_set<StmtNum> expected_stmt_for_print = { 4 };
            Assert::IsTrue(*print_with_var == expected_stmt_for_print);

            shared_ptr<unordered_set<StmtNum>> read_with_var = read->GetReadStatementFromVariable("x");
            unordered_set<StmtNum> expected_stmt_for_read = { 8 };
            Assert::IsTrue(*read_with_var == expected_stmt_for_read);

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

            // Check for if and while patterns
            shared_ptr<vector<pair<StmtNum, Variable>>> if_patterns = read->GetAllIfPatterns();
            vector<pair<StmtNum, Variable>> expected_if_patterns = {
                make_pair(7, "y"),
                make_pair(15, "call"),
                make_pair(18, "x"),
            };
            Assert::IsTrue(*if_patterns == expected_if_patterns);

            shared_ptr<vector<pair<StmtNum, Variable>>> while_patterns = read->GetAllWhilePatterns();
            vector<pair<StmtNum, Variable>> expected_while_patterns = {
                make_pair(3, "x"),
                make_pair(12, "x"),
                make_pair(20, "x"),
            };
            Assert::IsTrue(*while_patterns == expected_while_patterns);
        }

        TEST_METHOD(TestUsesRelationPopulation) {
            this->write->ResetPKB();
            UsesModifiesExtractor extractor(this->write);
            this->common_root->Extract(extractor);

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
            this->write->ResetPKB();
            UsesModifiesExtractor extractor(this->write);
            this->common_root->Extract(extractor);

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
            this->write->ResetPKB();
            ParentsExtractor extractor(this->write);
            this->common_root->Extract(extractor);

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
            this->write->ResetPKB();
            FollowsExtractor extractor(this->write);
            this->common_root->Extract(extractor);

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

        TEST_METHOD(TestCallsRelationPopulation) {
            this->write->ResetPKB();
            string calls_test_file = this->base_dir + "calls_extraction_test_source.txt";
            SourceParser parser = SourceParser();
            SourceLexer lexer = SourceLexer(calls_test_file);
            parser.SetTokens(lexer.GetAllTokens());
            shared_ptr<ProgramNode> calls_root = parser.Parse();

            CallsExtractor extractor(this->write);
            calls_root->Extract(extractor);

            // Calls is true for directly called procedure, but not for indirectly called ones
            Assert::IsTrue(this->read->CheckCalls("first", "second"));
            Assert::IsTrue(this->read->CheckCalls("first", "fourth"));
            Assert::IsFalse(this->read->CheckCalls("first", "third"));

            // Calls is true also in if and while statements
            Assert::IsTrue(this->read->CheckCalls("fourth", "fifth"));
            Assert::IsFalse(this->read->CheckCalls("fourth", "third"));

            Assert::IsTrue(this->read->CheckCalls("second", "third"));

            // Calls* is true for both directly and indirectly called procedures
            Assert::IsTrue(this->read->CheckCallsT("first", "second"));
            Assert::IsTrue(this->read->CheckCallsT("first", "fourth"));
            Assert::IsTrue(this->read->CheckCallsT("first", "third"));
            Assert::IsTrue(this->read->CheckCallsT("first", "fifth"));
            
            Assert::IsTrue(this->read->CheckCallsT("second", "third"));
            Assert::IsTrue(this->read->CheckCallsT("fourth", "fifth"));
            Assert::IsTrue(this->read->CheckCallsT("fourth", "third"));
            Assert::IsFalse(this->read->CheckCallsT("fourth", "second"));
        }

        TEST_METHOD(TestNextRelationPopulation) {
            this->write->ResetPKB();
            string next_test_file = this->base_dir + "next_extraction_test_source.txt";
            SourceParser parser = SourceParser();
            SourceLexer lexer = SourceLexer(next_test_file);
            parser.SetTokens(lexer.GetAllTokens());
            shared_ptr<ProgramNode> next_root = parser.Parse();

            NextExtractor extractor(this->write);
            next_root->Extract(extractor);

            // Test Next for statement of same nesting level in procedure
            Assert::IsTrue(this->read->CheckNext(1, 2));
            Assert::IsTrue(this->read->CheckNext(2, 3));
            Assert::IsFalse(this->read->CheckNext(3, 7));
            Assert::IsTrue(this->read->CheckNext(7, 8));
            Assert::IsTrue(this->read->CheckNext(9, 13));
            Assert::IsFalse(this->read->CheckNext(1, 3));
            Assert::IsFalse(this->read->CheckNext(7, 9));

            // Test Next is not true across last statement and first statement of procedures
            Assert::IsFalse(this->read->CheckNext(13, 14));
            Assert::IsFalse(this->read->CheckNext(23, 24));
            Assert::IsFalse(this->read->CheckNext(31, 32));
            Assert::IsFalse(this->read->CheckNext(38, 39));

            // Test Next for statement within if statements, 
            // and statements within for different blocks
            Assert::IsTrue(this->read->CheckNext(4, 5));
            Assert::IsFalse(this->read->CheckNext(5, 6));
            Assert::IsFalse(this->read->CheckNext(4, 6));

            Assert::IsTrue(this->read->CheckNext(15, 16));
            Assert::IsTrue(this->read->CheckNext(17, 18));
            Assert::IsFalse(this->read->CheckNext(16, 17));
            Assert::IsFalse(this->read->CheckNext(15, 17));

            // Test Next for statement within while statements
            Assert::IsTrue(this->read->CheckNext(10, 11));
            Assert::IsTrue(this->read->CheckNext(11, 12));
            Assert::IsFalse(this->read->CheckNext(12, 13));
            Assert::IsFalse(this->read->CheckNext(10, 9));
            Assert::IsFalse(this->read->CheckNext(11, 9));

            // Test Next for split route between last statement in if statements
            Assert::IsTrue(this->read->CheckNext(5, 7));
            Assert::IsTrue(this->read->CheckNext(6, 7));
            Assert::IsTrue(this->read->CheckNext(16, 19));
            Assert::IsTrue(this->read->CheckNext(18, 19));
            Assert::IsTrue(this->read->CheckNext(34, 37));
            Assert::IsTrue(this->read->CheckNext(36, 37));

            // Test loopback of while statements
            Assert::IsTrue(this->read->CheckNext(12, 9));
            Assert::IsFalse(this->read->CheckNext(11, 9));
            Assert::IsTrue(this->read->CheckNext(26, 25));
            Assert::IsFalse(this->read->CheckNext(25, 25));
            Assert::IsTrue(this->read->CheckNext(38, 37));

            // Test while statement after if statements
            Assert::IsFalse(this->read->CheckNext(33, 37));
            Assert::IsFalse(this->read->CheckNext(36, 38));

            // Test if inside if statements (4 possible paths to following statement)
            Assert::IsTrue(this->read->CheckNext(48, 53));
            Assert::IsTrue(this->read->CheckNext(49, 53));
            Assert::IsTrue(this->read->CheckNext(51, 53));
            Assert::IsTrue(this->read->CheckNext(52, 53));

            // Test if inside while statements 
            Assert::IsTrue(this->read->CheckNext(57, 54));
            Assert::IsTrue(this->read->CheckNext(58, 54));
            Assert::IsFalse(this->read->CheckNext(56, 54));
            Assert::IsFalse(this->read->CheckNext(55, 54));
            Assert::IsFalse(this->read->CheckNext(54, 54));
        }
    };
}