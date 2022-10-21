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
            std::shared_ptr<ProgramNode> root = parser.Parse();
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
    };
}