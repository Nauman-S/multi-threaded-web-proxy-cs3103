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
		
		TEST_CLASS_INITIALIZE(Initialization) {
			DesignExtractor extractor;
			SourceParser parser;
			SourceLexer lexer = SourceLexer(base_dir + "test_affects_relation_source.txt");
			std::shared_ptr<ProgramNode> root = parser.Parse(lexer.GetAllTokens());
			extractor.PopulatePKB(root);
		}

		TEST_METHOD(TestAffectsNoNesting) {
			Assert::IsTrue(read->CheckAffects(1, 3));
			Assert::IsTrue(read->CheckAffects(2, 6));
			//Assert::IsFalse(read->CheckAffects(1, 5));
		}

		TEST_METHOD(TestAffectsOnIfStatement) {
			Assert::IsTrue(read->CheckAffects(7, 11));
		}
	};
}