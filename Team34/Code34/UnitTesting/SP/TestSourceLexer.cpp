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
		string base_dir = "../../Tests34/unit_tests/lexer/";
		TEST_METHOD(TestNoSpaceSource)
		{
			SourceLexer lexer = SourceLexer(base_dir + "no_space_source.txt");
			shared_ptr<vector<SourceToken>> actual = lexer.GetAllTokens();
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
			Assert::IsTrue(actual->size() == expected.size());
			for (unsigned int i = 0; i < actual->size(); i++) {
				Assert::IsTrue(actual->at(i) == expected.at(i));
			}
		}

		TEST_METHOD(TestMultiSpaceSource)
		{
			SourceLexer lexer = SourceLexer(base_dir + "multi_space_source.txt");
			shared_ptr<vector<SourceToken>> actual = lexer.GetAllTokens();
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
			Assert::IsTrue(actual->size() == expected.size());
			for (unsigned int i = 0; i < actual->size(); i++) {
				Assert::IsTrue(actual->at(i) == expected.at(i));
			}
		}

		TEST_METHOD(TestMultiCharacterTokens)
		{
			SourceLexer lexer = SourceLexer(base_dir + "multi_token_source.txt");
			shared_ptr<vector<SourceToken>> actual = lexer.GetAllTokens();
			vector<SourceToken> expected = {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "while"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreaterEqual, ">="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalOr, "||"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kDoubleEqual, "=="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalAnd, "&&"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kLesserEqual, "<="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalOr, "||"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kNotEqual, "!="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			};
			Assert::IsTrue(actual->size() == expected.size());
			for (unsigned int i = 0; i < actual->size(); i++) {
				Assert::IsTrue(actual->at(i) == expected.at(i));
			}
		}

		TEST_METHOD(TestIfStatementSource)
		{
			SourceLexer lexer = SourceLexer(base_dir + "if_stmt_source.txt");
			shared_ptr<vector<SourceToken>> actual = lexer.GetAllTokens();
			vector<SourceToken> expected = {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "2"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "5"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			};
			Assert::IsTrue(actual->size() == expected.size());
			for (unsigned int i = 0; i < actual->size(); i++) {
				Assert::IsTrue(actual->at(i) == expected.at(i));
			}
		}

		TEST_METHOD(TestKeywordVariables)
		{
			SourceLexer lexer = SourceLexer(base_dir + "keyword_token_source.txt");
			shared_ptr<vector<SourceToken>> actual = lexer.GetAllTokens();
			vector<SourceToken> expected = {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "while"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			};
			Assert::IsTrue(actual->size() == expected.size());
			for (unsigned int i = 0; i < actual->size(); i++) {
				Assert::IsTrue(actual->at(i) == expected.at(i));
			}
		}

		TEST_METHOD(TestArithmeticExpression)
		{
			SourceLexer lexer = SourceLexer(base_dir + "complex_arithmetic_source.txt");
			shared_ptr<vector<SourceToken>> actual = lexer.GetAllTokens();
			vector<SourceToken> expected = {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kInteger, "9"),
				SourceToken(SourceTokenType::kMinus, "-"),
				SourceToken(SourceTokenType::kInteger, "2"),
				SourceToken(SourceTokenType::kModulo, "%"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kMinus, "-"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kMinus, "-"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			};
			Assert::IsTrue(actual->size() == expected.size());
			for (unsigned int i = 0; i < actual->size(); i++) {
				Assert::IsTrue(actual->at(i) == expected.at(i));
			}
		}
	};
}