#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>
#include <string>
#include <iostream>

#include "../SPA/PKB/ReadPKBManager.h"
#include "../SPA/PKB/WritePKBManager.h"

#include "../SPA/SP/SourceParser.h"
#include "../SPA/SP/tokenizer/SourceLexer.h"

#include "../SPA/SP/design_extractor/DesignExtractor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting
{		
    TEST_CLASS(TestAffectsRelationship)
    {
    private:
        inline static string base_dir = "../../Tests34/integration_tests/SP_PKB/";

        shared_ptr<ReadPKBManager> read = ReadPKBManager::GetInstance();
        inline static shared_ptr<WritePKBManager> write = WritePKBManager::GetInstance();
    public:
        
        TEST_CLASS_INITIALIZE(Initialization)
        {
            write->ResetPKB();
            DesignExtractor extractor;
            SourceParser parser;
            SourceLexer lexer = SourceLexer(base_dir + "test_affects_relation_source.txt");
            parser.SetTokens(lexer.GetAllTokens());
            std::shared_ptr<ProgramNode> root = parser.Parse();
            extractor.PopulatePKB(root);
        }

        TEST_METHOD(TestCheckAffectsNoNesting)
        {
            Assert::IsTrue(read->CheckAffects(1, 3));
            Assert::IsTrue(read->CheckAffects(2, 6));
            Assert::IsTrue(read->CheckAffects(4, 5));
            Assert::IsFalse(read->CheckAffects(1, 5));
            Assert::IsFalse(read->CheckAffects(4, 3));
        }

        TEST_METHOD(TestCheckAffectsForReadCalls) 
        {
            // Read modification
            Assert::IsTrue(read->CheckAffects(18, 22));
            Assert::IsTrue(read->CheckAffects(19, 22));
            Assert::IsTrue(read->CheckAffects(19, 23));
            Assert::IsFalse(read->CheckAffects(20, 22));
            Assert::IsFalse(read->CheckAffects(20, 23));

            // Calls modification
            Assert::IsTrue(read->CheckAffects(25, 27));
            Assert::IsFalse(read->CheckAffects(24, 27));
        }

        TEST_METHOD(TestCheckAffectsOnIfStatement)
        {
            Assert::IsTrue(read->CheckAffects(7, 11));
            Assert::IsTrue(read->CheckAffects(7, 12));
            Assert::IsTrue(read->CheckAffects(10, 12));
            Assert::IsFalse(read->CheckAffects(10, 11));
        }

        TEST_METHOD(TestCheckAffectsOnWhileLoop)
        {
            Assert::IsTrue(read->CheckAffects(13, 15));
            Assert::IsTrue(read->CheckAffects(13, 16));
            Assert::IsTrue(read->CheckAffects(13, 17));
            Assert::IsTrue(read->CheckAffects(15, 15));
            Assert::IsTrue(read->CheckAffects(16, 16));
            Assert::IsTrue(read->CheckAffects(16, 17));
            Assert::IsTrue(read->CheckAffects(16, 15));
            Assert::IsFalse(read->CheckAffects(15, 14));
            Assert::IsFalse(read->CheckAffects(16, 14));
        }

        TEST_METHOD(TestCheckAffectsOnIfWhileProcedure)
        {
            Assert::IsTrue(read->CheckAffects(29, 33));
            Assert::IsTrue(read->CheckAffects(30, 32));
            Assert::IsTrue(read->CheckAffects(38, 37));
        }

        TEST_METHOD(TestGetEffectStmtsFromStmtNoNesting)
        {
            shared_ptr<unordered_set<StmtNum>> effect_stmts_1 = read->GetEffectStmtsFromStmt(1, RefType::kAssignRef);
            Assert::IsTrue(effect_stmts_1->find(3) != effect_stmts_1->end());

            shared_ptr<unordered_set<StmtNum>> effect_stmts_2 = read->GetEffectStmtsFromStmt(2, RefType::kAssignRef);
            Assert::IsTrue(effect_stmts_2->find(6) != effect_stmts_2->end());
            Assert::AreEqual(0, int(read->GetEffectStmtsFromStmt(3, RefType::kAssignRef)->size()));

            shared_ptr<unordered_set<StmtNum>> effect_stmts_4 = read->GetEffectStmtsFromStmt(4, RefType::kAssignRef);
            Assert::IsTrue(effect_stmts_4->find(5) != effect_stmts_4->end());

            Assert::AreEqual(0, int(read->GetEffectStmtsFromStmt(5, RefType::kAssignRef)->size()));

            Assert::AreEqual(0, int(read->GetEffectStmtsFromStmt(6, RefType::kAssignRef)->size()));
        }

        TEST_METHOD(TestGetEffectStmtsFromStmtOnIfStatement)
        {
            shared_ptr<unordered_set<StmtNum>> effect_stmts_7 = read->GetEffectStmtsFromStmt(7, RefType::kAssignRef);
            Assert::IsTrue(effect_stmts_7->find(11) != effect_stmts_7->end());
            Assert::IsTrue(effect_stmts_7->find(12) != effect_stmts_7->end());

            Assert::AreEqual(0, int(read->GetEffectStmtsFromStmt(9, RefType::kAssignRef)->size()));

            shared_ptr<unordered_set<StmtNum>> effect_stmts_10 = read->GetEffectStmtsFromStmt(10, RefType::kAssignRef);

            Assert::IsTrue(effect_stmts_7->find(12) != effect_stmts_7->end());
        }

        TEST_METHOD(TestGetEffectStmtsFromStmtOnWhileLoop)
        {
            shared_ptr<unordered_set<StmtNum>> effect_stmts_13 = read->GetEffectStmtsFromStmt(13, RefType::kAssignRef);
            Assert::IsTrue(effect_stmts_13->find(15) != effect_stmts_13->end());
            Assert::IsTrue(effect_stmts_13->find(16) != effect_stmts_13->end());
            Assert::IsTrue(effect_stmts_13->find(17) != effect_stmts_13->end());

            shared_ptr<unordered_set<StmtNum>> effect_stmts_15 = read->GetEffectStmtsFromStmt(15, RefType::kAssignRef);
            Assert::IsTrue(effect_stmts_15->find(15) != effect_stmts_15->end());

            shared_ptr<unordered_set<StmtNum>> effect_stmts_16 = read->GetEffectStmtsFromStmt(16, RefType::kAssignRef);
            Assert::IsTrue(effect_stmts_16->find(15) != effect_stmts_16->end());
            Assert::IsTrue(effect_stmts_16->find(16) != effect_stmts_16->end());
            Assert::IsTrue(effect_stmts_16->find(17) != effect_stmts_16->end());
        }

        TEST_METHOD(TestGetCauseStmtsFromStmtNoNesting)
        {
            shared_ptr<unordered_set<StmtNum>> cause_stmts_3 = read->GetCauseStmtsFromStmt(3, RefType::kAssignRef);
            Assert::IsTrue(cause_stmts_3->find(1) != cause_stmts_3->end());

            shared_ptr<unordered_set<StmtNum>> cause_stmts_5 = read->GetCauseStmtsFromStmt(5, RefType::kAssignRef);
            Assert::IsTrue(cause_stmts_5->find(4) != cause_stmts_5->end());

            shared_ptr<unordered_set<StmtNum>> cause_stmts_6 = read->GetCauseStmtsFromStmt(6, RefType::kAssignRef);
            Assert::IsTrue(cause_stmts_6->find(2) != cause_stmts_6->end());
        }

        TEST_METHOD(TestGetCauseStmtsFromStmtOnIfStatement)
        {
            shared_ptr<unordered_set<StmtNum>> cause_stmts_11 = read->GetCauseStmtsFromStmt(11, RefType::kAssignRef);
            Assert::IsTrue(cause_stmts_11->find(7) != cause_stmts_11->end());

            shared_ptr<unordered_set<StmtNum>> cause_stmts_12 = read->GetCauseStmtsFromStmt(12, RefType::kAssignRef);
            Assert::IsTrue(cause_stmts_12->find(7) != cause_stmts_12->end());
            Assert::IsTrue(cause_stmts_12->find(10) != cause_stmts_12->end());
        }

        TEST_METHOD(TestGetCauseStmtsFromStmtOnWhileLoop)
        {
            shared_ptr<unordered_set<StmtNum>> cause_stmts_15 = read->GetCauseStmtsFromStmt(15, RefType::kAssignRef);
            Assert::IsTrue(cause_stmts_15->find(13) != cause_stmts_15->end());
            Assert::IsTrue(cause_stmts_15->find(15) != cause_stmts_15->end());
            Assert::IsTrue(cause_stmts_15->find(16) != cause_stmts_15->end());

            shared_ptr<unordered_set<StmtNum>> cause_stmts_16 = read->GetCauseStmtsFromStmt(16, RefType::kAssignRef);
            Assert::IsTrue(cause_stmts_16->find(13) != cause_stmts_16->end());
            Assert::IsTrue(cause_stmts_16->find(16) != cause_stmts_16->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsNoNesting)
        {
            shared_ptr<unordered_set<StmtNum>> actual = read->GetAllEffectStmts(RefType::kAssignRef);
            Assert::IsTrue(actual->find(3) != actual->end());
            Assert::IsTrue(actual->find(5) != actual->end());
            Assert::IsTrue(actual->find(6) != actual->end());
            Assert::IsFalse(actual->find(4) != actual->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsSingleIf)
        {
            shared_ptr<unordered_set<StmtNum>> actual = read->GetAllEffectStmts(RefType::kAssignRef);
            Assert::IsTrue(actual->find(11) != actual->end());
            Assert::IsTrue(actual->find(12) != actual->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsSingleWhile)
        {
            shared_ptr<unordered_set<StmtNum>> actual = read->GetAllEffectStmts(RefType::kAssignRef);
            Assert::IsTrue(actual->find(15) != actual->end());
            Assert::IsTrue(actual->find(16) != actual->end());
            Assert::IsTrue(actual->find(17) != actual->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsIfWhile)
        {
            shared_ptr<unordered_set<StmtNum>> actual = read->GetAllEffectStmts(RefType::kAssignRef);
            Assert::IsTrue(actual->find(32) != actual->end());
            Assert::IsTrue(actual->find(33) != actual->end());
            Assert::IsTrue(actual->find(33) != actual->end());
            Assert::IsTrue(actual->find(37) != actual->end());
            Assert::IsFalse(actual->find(34) != actual->end());
        }

        TEST_METHOD(TestGetAllCauseStmtsNoNesting)
        {
            shared_ptr<unordered_set<StmtNum>> actual = read->GetAllCauseStmts(RefType::kAssignRef);
            Assert::IsTrue(actual->find(1) != actual->end());
            Assert::IsTrue(actual->find(2) != actual->end());
            Assert::IsTrue(actual->find(4) != actual->end());
        }

        TEST_METHOD(TestGetAllCauseStmtsSingleIf)
        {
            shared_ptr<unordered_set<StmtNum>> actual = read->GetAllCauseStmts(RefType::kAssignRef);
            Assert::IsTrue(actual->find(7) != actual->end());
        }

        TEST_METHOD(TestGetAllCauseStmtsSingleWhile)
        {
            shared_ptr<unordered_set<StmtNum>> actual = read->GetAllCauseStmts(RefType::kAssignRef);
            Assert::IsTrue(actual->find(13) != actual->end());
            Assert::IsTrue(actual->find(15) != actual->end());
            Assert::IsTrue(actual->find(16) != actual->end());
        }

        TEST_METHOD(TestGetAllCauseStmtsIfWhile)
        {
            shared_ptr<unordered_set<StmtNum>> actual = read->GetAllCauseStmts(RefType::kAssignRef);
            Assert::IsTrue(actual->find(29) != actual->end());
            Assert::IsTrue(actual->find(30) != actual->end());
            Assert::IsTrue(actual->find(38) != actual->end());
        }


        TEST_METHOD(TestIsEmpty)
        {
            DesignExtractor extractor;
            SourceParser parser;

            // Test source file with no affects relation
            write->ResetPKB();
            SourceLexer lexer_empty_affects = SourceLexer(base_dir + "no_affects_relation_source.txt");
            parser.SetTokens(lexer_empty_affects.GetAllTokens());
            std::shared_ptr<ProgramNode> root_empty_affects = parser.Parse();
            extractor.PopulatePKB(root_empty_affects);
            Assert::IsTrue(read->IsAffectsStoreEmpty());

            // Test source file with some affects relation
            write->ResetPKB();
            SourceLexer lexer_has_affects = SourceLexer(base_dir + "some_affects_relation_source.txt");
            SourceParser parser_some;
            parser_some.SetTokens(lexer_has_affects.GetAllTokens());
            std::shared_ptr<ProgramNode> root_has_affects = parser_some.Parse();
            extractor.PopulatePKB(root_has_affects);
            Assert::IsFalse(read->IsAffectsStoreEmpty());

            // Repopulate PKB in event of random order test
            write->ResetPKB();
            SourceLexer lexer = SourceLexer(base_dir + "test_affects_relation_source.txt");
            SourceParser parser_re;
            parser_re.SetTokens(lexer.GetAllTokens());
            std::shared_ptr<ProgramNode> root = parser_re.Parse();
            extractor.PopulatePKB(root);
        }

        TEST_METHOD(TestGetAllAffectsRelations)
        {
            std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> actual = read->GetAllAffectsRelations();
            Assert::AreEqual(20, int(actual->size()));
            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(1, 3)) != actual->end());
            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(2, 6)) != actual->end());
            Assert::IsFalse(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(1, 5)) != actual->end());

            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(7, 11)) != actual->end());
            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(7, 12)) != actual->end());

            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(15, 15)) != actual->end());
            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(16, 15)) != actual->end());

            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(29, 33)) != actual->end());
            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(38, 37)) != actual->end());
        }

    };
}