#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../SPA/SP/tokenizer/SourceLexer.h"
#include "../../SPA/SP/tokenizer/SourceToken.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{		
	TEST_CLASS(TestSourceLexer)
	{
	public:
		string base_dir = "../../Tests34/unit_tests/";
		TEST_METHOD(TestNoSpaceSource)
		{
			SourceLexer lexer = SourceLexer(base_dir + "no_space_source.txt");
			vector<SourceToken> actual = lexer.GetAllTokens();
			vector<SourceToken> expected = {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			};
			Assert::IsTrue(actual.size() == expected.size());
			for (unsigned int i = 0; i < actual.size(); i++) {
				Assert::IsTrue(actual.at(i) == expected.at(i));
			}
		}

		TEST_METHOD(TestMultiSpaceSource)
		{
			SourceLexer lexer = SourceLexer(base_dir + "multi_space_source.txt");
			vector<SourceToken> actual = lexer.GetAllTokens();
			vector<SourceToken> expected = {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "PROC"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "abc1"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1023"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			};
			Assert::IsTrue(actual.size() == expected.size());
			for (unsigned int i = 0; i < actual.size(); i++) {
				Assert::IsTrue(actual.at(i) == expected.at(i));
			}
		}
	};
}