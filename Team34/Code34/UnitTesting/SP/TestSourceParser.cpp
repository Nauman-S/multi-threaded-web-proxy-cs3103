#include "stdafx.h"
#include "CppUnitTest.h"


#include "../../SPA/SP/SourceParser.h"
#include "../../SPA/SP/tokenizer/SourceToken.h"
#include "../../SPA/SP/tokenizer/SourceLexer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
	TEST_CLASS(TestSourceParser)
	{
	public:
		string base_dir = "../../Tests34/unit_tests/parser";
		TEST_METHOD(MultipleProc)
		{
			SourceParser parser = SourceParser();
            SourceLexer lexer = SourceLexer(base_dir + "/multiple_proc.txt");
			parser.SetTokens(lexer.GetAllTokens());
			std::shared_ptr<ProgramNode> root = parser.Parse().first;
			string actual = root->Stringify();
			string expected = "ProgramProcedureReadxReadzCallSecondProcedureAssignxx0Assignii5\
WhileCondition0iAssignxx2xyCallThirdAssignii1iifCondition1xAssignxx1xAssignzz1AssignzzzxiAssignyy2z\
AssignxxxyzProcedureAssignzz5AssignvvzPrintv";
			Assert::IsTrue(actual == expected);
		};

        TEST_METHOD(BasicStmt) {
            SourceParser parser = SourceParser();
            SourceLexer lexer = SourceLexer(base_dir + "/basic_stmt.txt");
			parser.SetTokens(lexer.GetAllTokens());
            std::shared_ptr<ProgramNode> root = parser.Parse().first;
            string actual = root->Stringify();
            string expected = "ProgramProcedureReadxWhileCondition2xAssignyy12345ifConditionyx\
Callproc2PrintzProcedurePrintx";
            Assert::IsTrue(actual == expected);
        };
		TEST_METHOD(ComplexCalls) {
			SourceParser parser = SourceParser();
			SourceLexer lexer = SourceLexer(base_dir + "/complex_calls_1.txt");
			parser.SetTokens(lexer.GetAllTokens());
			std::shared_ptr<ProgramNode> root = parser.Parse().first;
			string actual = root->Stringify();
			string expected = "ProgramProcedureCallproc2Callproc5ProcedureCallproc3Callproc4\
ProcedurePrintproc3ProcedurePrintproc4ProcedurePrintproc6ProcedureCallproc7Callproc8Callproc9\
ProcedurePrintproc7ProcedurePrintproc8ProcedurePrintproc9";
			Assert::IsTrue(actual == expected);
		};
		TEST_METHOD(LongProgram) {
			SourceParser parser = SourceParser();
			SourceLexer lexer = SourceLexer(base_dir + "/long_program.txt");
			parser.SetTokens(lexer.GetAllTokens());
			std::shared_ptr<ProgramNode> root = parser.Parse().first;
			string actual = root->Stringify();
			string expected = "ProgramProcedureAssignflagflag0CallcomputeCentroidCallprintResults\
ProcedureReadxReadyProcedurePrintflagPrintcenXPrintcenYPrintnormSqProcedureAssigncountcount0AssigncenXcenX0\
AssigncenYcenY0CallreadPointWhileCondition00xyAssigncountcount1countAssigncenXcenXcenXxAssigncenYcenYcenYy\
CallreadPointifCondition0countAssignflagflag1AssigncenXcenXcenXcountAssigncenYcenYcenYcountAssignnormSqnormSqcenXcenXcenYcenY";
			Assert::IsTrue(actual == expected);
		};
		TEST_METHOD(CallList1) {
			SourceParser parser = SourceParser();
			SourceLexer lexer = SourceLexer(base_dir + "/complex_calls_1.txt");
			parser.SetTokens(lexer.GetAllTokens());
			vector<Procedure> calls = parser.Parse().second;
			string actual;
			for (auto x : calls) {
				actual = actual + x + " ";
			}
			ofstream myfile;
			myfile.open("example.txt");
			myfile << actual;
			myfile.close();
			string expected = "proc6 proc9 proc8 proc7 proc1 proc5 proc2 proc4 proc3 ";
			Assert::IsTrue(actual == expected);
		};
		TEST_METHOD(CallList2) {
			SourceParser parser = SourceParser();
			SourceLexer lexer = SourceLexer(base_dir + "/complex_calls_2.txt");
			parser.SetTokens(lexer.GetAllTokens());
			vector<Procedure> calls = parser.Parse().second;
			string actual;
			for (auto x : calls) {
				actual = actual + x + " ";
			}
			string expected = "proc5 proc1 proc6 proc9 proc8 proc7 proc2 proc4 proc3 ";
			Assert::IsTrue(actual == expected);
		};
		TEST_METHOD(CallList3) {
			SourceParser parser = SourceParser();
			SourceLexer lexer = SourceLexer(base_dir + "/long_program.txt");
			parser.SetTokens(lexer.GetAllTokens());
			vector<Procedure> calls = parser.Parse().second;
			string actual;
			for (auto x : calls) {
				actual = actual + x + " ";
			}
			string expected = "main printResults computeCentroid readPoint ";
			Assert::IsTrue(actual == expected);
		};
		TEST_METHOD(CallList4) {
			SourceParser parser = SourceParser();
			SourceLexer lexer = SourceLexer(base_dir + "/stress_test.txt");
			parser.SetTokens(lexer.GetAllTokens());
			vector<Procedure> calls = parser.Parse().second;
			string actual;
			for (auto x : calls) {
				actual = actual + x + " ";
			}
			string expected = "P90 P87 P86 P88 P84 P75 P73 P71 P69 P67 P66 P62 P57 P56 P55 \
P51 P50 P48 P42 P95 P37 P34 P13 P52 P12 P26 P29 P100 P63 P65 P92 P31 P1 P43 P74 P33 P2 P24 \
P38 P46 P82 P83 P61 P59 P36 P11 P25 P19 P93 P64 P58 P53 P23 P45 P35 P68 P10 P6 P40 P41 P22 \
P96 P81 P85 P4 P14 P72 P27 P32 P3 P97 P99 P78 P47 P79 P70 P17 P77 P5 P89 P18 P7 P98 P21 P8 \
P91 P16 P9 P94 P15 P28 P20 P49 P60 P80 P44 P30 P39 P54 P76 StressTest ";
			Assert::IsTrue(actual == expected);
		};
	};
}