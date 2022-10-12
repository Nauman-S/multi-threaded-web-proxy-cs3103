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
	TEST_CLASS(TestAffectsRelationship)
	{
	private:
		inline static string base_dir = "../../Tests34/integration_tests/SP_PKB/";

		shared_ptr<ReadPKBManager> read = ReadPKBManager::GetInstance();
	public:
		
		TEST_CLASS_INITIALIZE(Initialization)
		{
			DesignExtractor extractor;
			SourceParser parser;
			SourceLexer lexer = SourceLexer(base_dir + "test_affects_relation_source.txt");
			std::shared_ptr<ProgramNode> root = parser.Parse(lexer.GetAllTokens());
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

		TEST_METHOD(TestGetEffectStmtsFromStmtNoNesting)
		{
			// Result: 3
			Assert::AreEqual(1, int(read->GetEffectStmtsFromStmt(1)->size()));
			// Result: 6
			Assert::AreEqual(1, int(read->GetEffectStmtsFromStmt(2)->size()));
			// Result: -
			Assert::AreEqual(0, int(read->GetEffectStmtsFromStmt(3)->size()));
			// Result: 5
			Assert::AreEqual(1, int(read->GetEffectStmtsFromStmt(4)->size()));
			// Result: -
			Assert::AreEqual(0, int(read->GetEffectStmtsFromStmt(5)->size()));
			// Result: -
			Assert::AreEqual(0, int(read->GetEffectStmtsFromStmt(6)->size()));	
		}

		TEST_METHOD(TestGetEffectStmtsFromStmtOnIfStatement)
		{
			// Result: 11, 12
			Assert::AreEqual(2, int(read->GetEffectStmtsFromStmt(7)->size()));
			// Result: -
			Assert::AreEqual(0, int(read->GetEffectStmtsFromStmt(9)->size()));
			// Result: 12
			Assert::AreEqual(1, int(read->GetEffectStmtsFromStmt(10)->size()));
		}

		TEST_METHOD(TestGetEffectStmtsFromStmtOnWhileLoop)
		{
			// Result: 15, 16, 17
			Assert::AreEqual(3, int(read->GetEffectStmtsFromStmt(13)->size()));
			// Result: 15
			Assert::AreEqual(1, int(read->GetEffectStmtsFromStmt(15)->size()));
			// Result: 15, 16, 17
			Assert::AreEqual(3, int(read->GetEffectStmtsFromStmt(16)->size()));
		}
	};
}