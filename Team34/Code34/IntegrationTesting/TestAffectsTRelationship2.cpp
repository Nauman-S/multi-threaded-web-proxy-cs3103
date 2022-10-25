#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>
#include <string>
#include <iostream>

#include "../SPA/PKB/ReadPKBManager.h"
#include "../SPA/PKB/WritePKBManager.h"

#include "../SPA/SP/SourceParser.h"
#include "../SPA/SP/tokenizer/SourceLexer.h"

#include "../SPA/SP/DesignExtractor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting
{
    TEST_CLASS(TestAffectsTRelationship2)
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
            SourceLexer lexer = SourceLexer(base_dir + "test_affects_T_relation_2_source.txt");
            parser.SetTokens(lexer.GetAllTokens());
            std::shared_ptr<ProgramNode> root = parser.Parse();
            extractor.PopulatePKB(root);
        }

        TEST_METHOD(TestCheckAffectsTBasic)
        {
            DesignExtractor extractor;
            SourceParser parser;

            // Test new source file for affectsT relation
            write->ResetPKB();
            SourceLexer lexer_empty_affects = SourceLexer(base_dir + "test_affects_T_relation_2_source.txt");
            parser.SetTokens(lexer_empty_affects.GetAllTokens());
            std::shared_ptr<ProgramNode> root_empty_affects = parser.Parse();
            extractor.PopulatePKB(root_empty_affects);

            Assert::IsTrue(read->CheckAffectsT(1, 3));
            Assert::IsTrue(read->CheckAffectsT(1, 4));
            Assert::IsFalse(read->CheckAffectsT(5, 8));
        }

        TEST_METHOD(TestCheckAffectsTCalls)
        {
            Assert::IsTrue(read->CheckAffectsT(10, 14));
            Assert::IsTrue(read->CheckAffectsT(11, 14));
        }

        TEST_METHOD(TestCheckAffectsTWhileStmt)
        {
            Assert::IsTrue(read->CheckAffectsT(15, 17));
            Assert::IsTrue(read->CheckAffectsT(19, 18));
            Assert::IsTrue(read->CheckAffectsT(19, 19));
        }

        TEST_METHOD(TestCheckAffectsTIfStmt)
        {
            Assert::IsTrue(read->CheckAffectsT(20, 25));
            Assert::IsTrue(read->CheckAffectsT(21, 27));
        }

        TEST_METHOD(TestGetAllEffectStmtsFromStmtBasic)
        {
            DesignExtractor extractor;
            SourceParser parser;

            // Test new source file for affectsT relation
            write->ResetPKB();
            SourceLexer lexer_empty_affects = SourceLexer(base_dir + "test_affects_T_relation_2_source.txt");
            parser.SetTokens(lexer_empty_affects.GetAllTokens());
            std::shared_ptr<ProgramNode> root_empty_affects = parser.Parse();
            extractor.PopulatePKB(root_empty_affects);

            std::shared_ptr<std::unordered_set<StmtNum>> all_effects = read->GetAllEffectStmtsFromStmt(1, RefType::kStmtRef);
            Assert::AreEqual(3, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(2) != all_effects->end());
            Assert::IsTrue(all_effects->find(3) != all_effects->end());
            Assert::IsTrue(all_effects->find(4) != all_effects->end());

            all_effects = read->GetAllEffectStmtsFromStmt(5, RefType::kStmtRef);
            Assert::AreEqual(1, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(6) != all_effects->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsFromStmtCalls)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_effects = read->GetAllEffectStmtsFromStmt(10, RefType::kStmtRef);
            Assert::AreEqual(2, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(11) != all_effects->end());
            Assert::IsTrue(all_effects->find(14) != all_effects->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsFromStmtWhileLoop)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_effects = read->GetAllEffectStmtsFromStmt(15, RefType::kStmtRef);
            Assert::AreEqual(3, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(17) != all_effects->end());
            Assert::IsTrue(all_effects->find(18) != all_effects->end());
            Assert::IsTrue(all_effects->find(19) != all_effects->end());

            all_effects = read->GetAllEffectStmtsFromStmt(17, RefType::kStmtRef);
            Assert::AreEqual(3, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(17) != all_effects->end());
            Assert::IsTrue(all_effects->find(18) != all_effects->end());
            Assert::IsTrue(all_effects->find(19) != all_effects->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsFromStmtIfLoop)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_effects = read->GetAllEffectStmtsFromStmt(20, RefType::kStmtRef);
            Assert::AreEqual(2, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(25) != all_effects->end());
            Assert::IsTrue(all_effects->find(27) != all_effects->end());

            all_effects = read->GetAllEffectStmtsFromStmt(21, RefType::kStmtRef);
            Assert::AreEqual(1, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(27) != all_effects->end());
        }


        TEST_METHOD(TestGetAllAffectsTRelation)
        {
            DesignExtractor extractor;
            SourceParser parser;

            // Test new source file for affectsT relation
            write->ResetPKB();
            SourceLexer lexer = SourceLexer(base_dir + "test_affects_T_relation_2_source.txt");
            parser.SetTokens(lexer.GetAllTokens());
            std::shared_ptr<ProgramNode> root = parser.Parse();
            extractor.PopulatePKB(root);

            std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> actual = read->GetAllAffectsTRelations();

            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(28, 30)) != actual->end());
            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(30, 33)) != actual->end());
            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(28, 36)) != actual->end());
            Assert::IsTrue(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(28, 39)) != actual->end());
            Assert::IsFalse(std::find(actual->begin(), actual->end(), std::make_pair<StmtNum, StmtNum>(39, 42)) != actual->end());
        }
    };
}