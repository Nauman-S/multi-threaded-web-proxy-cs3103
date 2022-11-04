#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>
#include <string>
#include <iostream>

#include "../SPA/SP/SourceParser.h"
#include "../SPA/SP/SourceValidator.h"
#include "../SPA/SP/tokenizer/SourceLexer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting {
    TEST_CLASS(TestSourceValidator) {
private:
    string path = "../../Tests34/integration_tests/SP_PKB/";

public:
    TEST_METHOD(StressTest1) {
        SourceLexer lexer = SourceLexer(path + "/stress_test.txt");
        SourceValidator validator = SourceValidator();
        shared_ptr<vector<SourceToken>> tokens = lexer.GetAllTokens();
        validator.SetTokens(tokens);
        bool actual = validator.Validate();
        bool expected = true;
        Assert::IsTrue(actual == expected);
    }
    };
}