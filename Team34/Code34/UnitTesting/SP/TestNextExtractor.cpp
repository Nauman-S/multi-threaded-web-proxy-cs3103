#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>

#include "../../SPA/SP/SourceParser.h"
#include "../../SPA/SP/tokenizer/SourceLexer.h"

#include "../../SPA/SP/stub/WritePKBManagerStub.h"

#include "../../SPA/SP/design_extractor/NextExtractor.h"
#include "../../SPA/SP/ast/ProgramNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{		
	TEST_CLASS(TestNextExtractor)
	{
	public:
		static inline std::shared_ptr<WritePKBManagerStub> write_stub;

		TEST_CLASS_INITIALIZE(Initialization) {
			std::shared_ptr<WritePKBManagerStub> stub(new WritePKBManagerStub());
			write_stub = stub;
			NextExtractor extractor = NextExtractor(write_stub);

			SourceParser parser;
			SourceLexer lexer = SourceLexer("../../Tests34/integration_tests/SP_PKB/design_extractor/next_extraction_test_source.txt");
			parser.SetTokens(lexer.GetAllTokens());
			std::shared_ptr<ProgramNode> root = parser.Parse();
			root->Extract(extractor);
		}

		TEST_METHOD(TestSingleBlockInProcedure)
		{
			Assert::IsTrue(write_stub->CheckCodeBlockSet(59, 62));
			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(59, 62));
		}

		TEST_METHOD(TestBlocksStayWithinProcedure)
		{
			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(13, 14));
			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(22, 24));
			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(37, 39));
		}

		TEST_METHOD(TestBlocksAroundIfStatement)
		{
			Assert::IsTrue(write_stub->CheckCodeBlockSet(1, 2));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(3, 3));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(1, 3));

			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(3, 4));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(3, 6));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(4, 5));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(6, 6));

			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(3, 7));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(4, 7));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(6, 7));
		}

		TEST_METHOD(TestBlocksAroundWhileStatement) {
			Assert::IsTrue(write_stub->CheckCodeBlockSet(9, 9));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(10, 12));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(13, 13));
			Assert::IsFalse(write_stub->CheckCodeBlockSet(9, 12));

			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(10, 9));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(9, 13));
			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(12, 9));
			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(12, 13));
		}

		TEST_METHOD(TestIfAfterIf) {
			Assert::IsTrue(write_stub->CheckCodeBlockSet(15, 16));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(17, 18));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(15, 19));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(17, 19));
			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(14, 19));
		}

		TEST_METHOD(WhileAfterIf) {
			Assert::IsTrue(write_stub->CheckCodeBlockSet(35, 36));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(34, 34));

			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(34, 37));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(35, 37));
			Assert::IsFalse(write_stub->CheckOptimisedEdgeSet(33, 37));
		}

		TEST_METHOD(WhileInIf) {
			Assert::IsTrue(write_stub->CheckCodeBlockSet(24, 24));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(25, 25));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(24, 25));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(26, 25));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(25, 27));
		}

		TEST_METHOD(IfInIf) {
			Assert::IsTrue(write_stub->CheckCodeBlockSet(48, 48));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(49, 49));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(51, 51));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(52, 52));

			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(48, 53));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(49, 53));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(51, 53));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(52, 53));
		}

		TEST_METHOD(IfInWhile) {
			Assert::IsTrue(write_stub->CheckCodeBlockSet(54, 54));
			Assert::IsTrue(write_stub->CheckCodeBlockSet(55, 55));
			Assert::IsFalse(write_stub->CheckCodeBlockSet(54, 55));

			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(57, 54));
			Assert::IsTrue(write_stub->CheckOptimisedEdgeSet(58, 54));
		}
	};
}