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
    TEST_CLASS(TestAffectsTRelationship)
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
            SourceLexer lexer = SourceLexer(base_dir + "test_affectsT_relation_source.txt");
            parser.SetTokens(lexer.GetAllTokens());
            std::shared_ptr<ProgramNode> root = parser.Parse().first;
            extractor.PopulatePKB(root);
        }

        TEST_METHOD(TestGetAllEffectStmtsFromStmtNoNesting)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_effects = read->GetAllEffectStmtsFromStmt(1, RefType::kStmtRef);
            Assert::AreEqual(3, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(3) != all_effects->end());
            Assert::IsTrue(all_effects->find(4) != all_effects->end());
            Assert::IsTrue(all_effects->find(6) != all_effects->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsFromStmtSingleIf)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_effects = read->GetAllEffectStmtsFromStmt(7, RefType::kStmtRef);
            Assert::AreEqual(4, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(9) != all_effects->end());
            Assert::IsTrue(all_effects->find(10) != all_effects->end());
            Assert::IsTrue(all_effects->find(11) != all_effects->end());
            Assert::IsTrue(all_effects->find(12) != all_effects->end());
        }

        TEST_METHOD(TestGetAllEffectStmtsFromStmtSingleWhile)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_effects = read->GetAllEffectStmtsFromStmt(13, RefType::kStmtRef);
            Assert::AreEqual(4, int(all_effects->size()));
            Assert::IsTrue(all_effects->find(15) != all_effects->end());
            Assert::IsTrue(all_effects->find(16) != all_effects->end());
            Assert::IsTrue(all_effects->find(17) != all_effects->end());
            Assert::IsTrue(all_effects->find(18) != all_effects->end());
        }

        TEST_METHOD(TestGetAllCauseStmtsFromStmtNoNesting)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_causes = read->GetAllCauseStmtsFromStmt(6, RefType::kStmtRef);
            Assert::AreEqual(3, int(all_causes->size()));
            Assert::IsTrue(all_causes->find(4) != all_causes->end());
            Assert::IsTrue(all_causes->find(3) != all_causes->end());
            Assert::IsTrue(all_causes->find(1) != all_causes->end());
        }

        TEST_METHOD(TestGetAllCauseStmtsFromStmtSingleIf)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_causes = read->GetAllCauseStmtsFromStmt(12, RefType::kStmtRef);
            Assert::AreEqual(3, int(all_causes->size()));
            Assert::IsTrue(all_causes->find(10) != all_causes->end());
            Assert::IsTrue(all_causes->find(9) != all_causes->end());
            Assert::IsTrue(all_causes->find(7) != all_causes->end());

            all_causes = read->GetAllCauseStmtsFromStmt(11, RefType::kStmtRef);
            Assert::AreEqual(1, int(all_causes->size()));
            Assert::IsTrue(all_causes->find(7) != all_causes->end());
        }

        TEST_METHOD(TestGetAllCauseStmtsFromStmtSingleWhile)
        {
            std::shared_ptr<std::unordered_set<StmtNum>> all_causes = read->GetAllCauseStmtsFromStmt(18, RefType::kStmtRef);
            Assert::AreEqual(1, int(all_causes->size()));
            Assert::IsTrue(all_causes->find(13) != all_causes->end());

            all_causes = read->GetAllCauseStmtsFromStmt(17, RefType::kStmtRef);
            Assert::AreEqual(3, int(all_causes->size()));
            Assert::IsTrue(all_causes->find(16) != all_causes->end());
            Assert::IsTrue(all_causes->find(15) != all_causes->end());
            Assert::IsTrue(all_causes->find(13) != all_causes->end());
        }
    };
}