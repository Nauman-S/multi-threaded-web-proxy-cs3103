#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../SPA/SP/SourceValidator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
	TEST_CLASS(TestSourceValidator)
	{
	public:
		string base_dir = "../../Tests34/unit_tests/validator";
		TEST_METHOD(BasicStmt)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken>{
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "while"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "2"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kInteger, "2"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kInteger, "3"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kInteger, "4"),
				SourceToken(SourceTokenType::kModulo, "%"),
				SourceToken(SourceTokenType::kInteger, "5"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc2"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "z"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc2"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = true;
			Assert::IsTrue(actual == true);
		};

		TEST_METHOD(ChildProcedure)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken>{
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "parent"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "child"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(ComplexCalls)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken>{
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc2"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc5"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc2"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc3"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc4"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc3"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "proc3"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc4"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "proc4"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc5"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "proc6"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc6"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc7"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc8"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc9"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc7"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "proc7"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc8"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "proc8"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc9"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "proc9"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),

			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(CyclicCall)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken>{
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc2"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc2"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc3"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc4"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc3"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc4"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(EmptyBody)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken>{
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "empty"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kRightCurly, "}"),

			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidArithmeticFormula_1)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken>{
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kMinus, "-"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kRightRound, ")"),
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
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidArithmeticFormula_2)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kRightRound, ")"),
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
				SourceToken(SourceTokenType::kLeftRound, "("),
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
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidConditionExpression_1)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kNegate, "!"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalOr, "||"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreaterEqual, ">="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalAnd, "&&"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kInteger, "3"),
				SourceToken(SourceTokenType::kMinus, "-"),
				SourceToken(SourceTokenType::kInteger, "6"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kInteger, "4"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kModulo, "%"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kDoubleEqual, "=="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "z"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidConditionExpression_2)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kNegate, "!"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalOr, "||"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreaterEqual, ">="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalAnd, "&&"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kInteger, "3"),
				SourceToken(SourceTokenType::kMinus, "-"),
				SourceToken(SourceTokenType::kInteger, "6"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kInteger, "4"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kModulo, "%"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "z"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidConditionExpression_3)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kNegate, "!"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalOr, "||"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreaterEqual, ">="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalAnd, "&&"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kInteger, "3"),
				SourceToken(SourceTokenType::kMinus, "-"),
				SourceToken(SourceTokenType::kInteger, "6"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kInteger, "4"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kModulo, "%"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kDoubleEqual, "=="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "z"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidKeyword_1)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "Procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidKeyword_2)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "Print"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidKeyword_3)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidKeyword_4)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "wHile"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidKeyword_5)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "wHile"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(KeywordVars)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kName, "while"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),

			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(LongProgram)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "main"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "flag"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "computeCentroid"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "printResults"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "readPoint"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "printResults"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "flag"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "normSq"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "computeCentroid"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "readPoint"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "while"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kNotEqual, "!="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalAnd, "&&"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kNotEqual, "!="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "readPoint"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kDoubleEqual, "=="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "flag"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "normSq"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(Nesting)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "while"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kLesser, "<"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "while"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidSemiColon)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "main"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "flag"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "computeCentroid"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "printResults"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "readPoint"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "printResults"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "flag"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "normSq"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "computeCentroid"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "readPoint"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "while"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kNotEqual, "!="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalAnd, "&&"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kNotEqual, "!="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kName, "y"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "call"),
				SourceToken(SourceTokenType::kName, "readPoint"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kDoubleEqual, "=="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "flag"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kName, "count"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "normSq"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kName, "cenX"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kName, "cenY"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(ValidArithmeticFormula)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kRightRound, ")"),
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
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(ValidConditionExpression)
		{
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub (new vector<SourceToken> {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "if"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kNegate, "!"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreater, ">"),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalOr, "||"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kGreaterEqual, ">="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kLogicalAnd, "&&"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kAdd, "+"),
				SourceToken(SourceTokenType::kInteger, "3"),
				SourceToken(SourceTokenType::kMinus, "-"),
				SourceToken(SourceTokenType::kInteger, "6"),
				SourceToken(SourceTokenType::kMultiply, "*"),
				SourceToken(SourceTokenType::kLeftRound, "("),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kDivide, "/"),
				SourceToken(SourceTokenType::kInteger, "4"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kModulo, "%"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kDoubleEqual, "=="),
				SourceToken(SourceTokenType::kInteger, "0"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kRightRound, ")"),
				SourceToken(SourceTokenType::kName, "then"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "z"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "else"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "x"),
				SourceToken(SourceTokenType::kEqual, "="),
				SourceToken(SourceTokenType::kInteger, "1"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
			});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(RepeatedProcedure) {
			SourceValidator validator = SourceValidator();
			shared_ptr<vector<SourceToken>> stub(new vector<SourceToken>{
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "read"),
				SourceToken(SourceTokenType::kName, "a"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "proc1"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kName, "print"),
				SourceToken(SourceTokenType::kName, "a"),
				SourceToken(SourceTokenType::kSemiColon, ";"),
				SourceToken(SourceTokenType::kRightCurly, "}"),
				});
			validator.SetTokens(stub);
			bool actual = validator.Validate();
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};
	};
}