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
			vector<SourceToken> stub = {
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
			};
			bool actual = validator.Validate(stub);
			bool expected = true;
			Assert::IsTrue(actual == true);
		};

		TEST_METHOD(ChildProcedure)
		{
			SourceValidator validator = SourceValidator();
			vector<SourceToken> stub = {
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
			};
			bool actual = validator.Validate(stub);
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(ComplexCalls)
		{
			SourceValidator validator = SourceValidator();
			vector<SourceToken> stub = {
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

			};
			bool actual = validator.Validate(stub);
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(CyclicCall)
		{
			SourceValidator validator = SourceValidator();
			vector<SourceToken> stub = {
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
			};
			bool actual = validator.Validate(stub);
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(EmptyBody)
		{
			SourceValidator validator = SourceValidator();
			vector<SourceToken> stub = {
				SourceToken(SourceTokenType::kName, "procedure"),
				SourceToken(SourceTokenType::kName, "empty"),
				SourceToken(SourceTokenType::kLeftCurly, "{"),
				SourceToken(SourceTokenType::kRightCurly, "}"),

			};
			bool actual = validator.Validate(stub);
			bool expected = true;
			Assert::IsTrue(actual == expected);
		};

		TEST_METHOD(InvalidArithmeticFormula_1)
		{
			SourceValidator validator = SourceValidator();
			vector<SourceToken> stub = {
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
			};
			bool actual = validator.Validate(stub);
			bool expected = false;
			Assert::IsTrue(actual == expected);
		};
	};
}