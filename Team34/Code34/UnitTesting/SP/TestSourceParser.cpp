#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../SPA/SP/SourceParser.h"
#include "../../SPA/SP/tokenizer/SourceToken.h"
#include "../../SPA/SP/tokenizer/SourceLexer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting {
    TEST_CLASS(TestSourceParser) {
public:
    string base_dir = "../../Tests34/unit_tests/parser";
    TEST_METHOD(MultipleProc) {
        SourceParser parser = SourceParser();
        SourceLexer lexer = SourceLexer(base_dir + "/multiple_proc.txt");
        parser.SetTokens(lexer.GetAllTokens());
        std::shared_ptr<ProgramNode> root = parser.Parse();
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
        std::shared_ptr<ProgramNode> root = parser.Parse();
        string actual = root->Stringify();
        string expected = "ProgramProcedureReadxWhileCondition2xAssignyy12345ifConditionyx\
Callproc2PrintzProcedurePrintx";
        Assert::IsTrue(actual == expected);
    };
    TEST_METHOD(ComplexCalls) {
        SourceParser parser = SourceParser();
        SourceLexer lexer = SourceLexer(base_dir + "/complex_calls_1.txt");
        parser.SetTokens(lexer.GetAllTokens());
        std::shared_ptr<ProgramNode> root = parser.Parse();
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
        std::shared_ptr<ProgramNode> root = parser.Parse();
        string actual = root->Stringify();
        string expected = "ProgramProcedureAssignflagflag0CallcomputeCentroidCallprintResults\
ProcedureReadxReadyProcedurePrintflagPrintcenXPrintcenYPrintnormSqProcedureAssigncountcount0AssigncenXcenX0\
AssigncenYcenY0CallreadPointWhileCondition00xyAssigncountcount1countAssigncenXcenXcenXxAssigncenYcenYcenYy\
CallreadPointifCondition0countAssignflagflag1AssigncenXcenXcenXcountAssigncenYcenYcenYcountAssignnormSqnormSqcenXcenXcenYcenY";
        Assert::IsTrue(actual == expected);
    };
    };
}