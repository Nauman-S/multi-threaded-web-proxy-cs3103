#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../SPA/SP/SourceParser.h"
#include "../../SPA/SP/tokenizer/SourceToken.h"
#include <fstream>
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
			std::shared_ptr<ProgramNode> root = parser.Parse(base_dir + "/multiple_proc.txt");
			string actual = root->Stringify();
			ofstream outfile;
			outfile.open("x.txt");
			outfile << actual << endl;
			string expected = "ProgramProcedureReadxReadzCallSecondProcedureAssignxx0Assignii5\
WhileCondition0iAssignxx2xyCallThirdAssignii1iifCondition1xAssignxx1xAssignzz1AssignzzzxiAssignyy2z\
AssignxxxyzProcedureAssignzz5AssignvvzPrintv";
			Assert::IsTrue(actual == expected);
		};
	};
}