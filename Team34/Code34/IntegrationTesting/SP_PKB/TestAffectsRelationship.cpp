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

		TEST_METHOD(TestGetCauseStmtsFromStmtNoNesting)
		{
			// Result: 1
			Assert::AreEqual(1, int(read->GetCauseStmtsFromStmt(3)->size()));
			// Result: 4
			Assert::AreEqual(1, int(read->GetCauseStmtsFromStmt(5)->size()));
			// Result: 3
			Assert::AreEqual(1, int(read->GetCauseStmtsFromStmt(6)->size()));
		}

		TEST_METHOD(TestGetCauseStmtsFromStmtOnIfStatement)
		{
			// Result: 7
			Assert::AreEqual(1, int(read->GetCauseStmtsFromStmt(11)->size()));
			// Result: 7, 10
			Assert::AreEqual(2, int(read->GetCauseStmtsFromStmt(12)->size()));
		}

		TEST_METHOD(TestGetCauseStmtsFromStmtOnWhileLoop)
		{
			shared_ptr<unordered_set<StmtNum>> actual_stmt_15 = read->GetCauseStmtsFromStmt(15);
			unordered_set<StmtNum> expected = {13, 15, 16};
			Assert::IsTrue(*actual_stmt_15 == expected);

			shared_ptr<unordered_set<StmtNum>> actual_stmt_16 = read->GetCauseStmtsFromStmt(16);
			expected = {13, 16};
			Assert::IsTrue(*actual_stmt_16 == expected);
		}

		TEST_METHOD(TestGetAllEffectStmtsNoNesting)
		{
			shared_ptr<unordered_set<StmtNum>> actual = read->GetAllEffectStmts();
			Assert::IsTrue(actual->find(3) != actual->end());
			Assert::IsTrue(actual->find(5) != actual->end());
			Assert::IsTrue(actual->find(6) != actual->end());
			Assert::IsFalse(actual->find(4) != actual->end());
		}

		TEST_METHOD(TestGetAllEffectStmtsSingleIf)
		{
			shared_ptr<unordered_set<StmtNum>> actual = read->GetAllEffectStmts();
			Assert::IsTrue(actual->find(11) != actual->end());
			Assert::IsTrue(actual->find(12) != actual->end());
		}

		TEST_METHOD(TestGetAllEffectStmtsSingleWhile)
		{
			shared_ptr<unordered_set<StmtNum>> actual = read->GetAllEffectStmts();
			Assert::IsTrue(actual->find(15) != actual->end());
			Assert::IsTrue(actual->find(16) != actual->end());
			Assert::IsTrue(actual->find(17) != actual->end());
		}

		TEST_METHOD(TestGetAllEffectStmtsIfWhile)
		{
			shared_ptr<unordered_set<StmtNum>> actual = read->GetAllEffectStmts();
			Assert::IsTrue(actual->find(32) != actual->end());
			Assert::IsTrue(actual->find(33) != actual->end());
			Assert::IsTrue(actual->find(33) != actual->end());
			Assert::IsTrue(actual->find(37) != actual->end());
			Assert::IsFalse(actual->find(34) != actual->end());
		}

		TEST_METHOD(TestGetAllCauseStmtsNoNesting)
		{
			shared_ptr<unordered_set<StmtNum>> actual = read->GetAllCauseStmts();
			Assert::IsTrue(actual->find(1) != actual->end());
			Assert::IsTrue(actual->find(2) != actual->end());
			Assert::IsTrue(actual->find(4) != actual->end());
		}

		TEST_METHOD(TestGetAllCauseStmtsSingleIf)
		{
			shared_ptr<unordered_set<StmtNum>> actual = read->GetAllCauseStmts();
			Assert::IsTrue(actual->find(7) != actual->end());
		}

		TEST_METHOD(TestGetAllCauseStmtsSingleWhile)
		{
			shared_ptr<unordered_set<StmtNum>> actual = read->GetAllCauseStmts();
			Assert::IsTrue(actual->find(13) != actual->end());
			Assert::IsTrue(actual->find(15) != actual->end());
			Assert::IsTrue(actual->find(16) != actual->end());
		}

		TEST_METHOD(TestGetAllCauseStmtsIfWhile)
		{
			shared_ptr<unordered_set<StmtNum>> actual = read->GetAllCauseStmts();
			Assert::IsTrue(actual->find(29) != actual->end());
			Assert::IsTrue(actual->find(30) != actual->end());
			Assert::IsTrue(actual->find(38) != actual->end());
		}
	};
}