#include "TestWrapper.h"

#include <iostream>
#include <optional>
#include <memory>
#include <map>

#include "../SPA/SP/tokenizer/SourceLexer.h"
#include "../SPA/SP/SourceValidator.h"
#include "../SPA/SP/SourceParser.h"
#include "../SPA/SP/design_extractor/DesignExtractor.h"

#include "../SPA/QPS/parser/QueryBuilder.h"
#include "../SPA/QPS/Query.h"
#include "../SPA/QPS/QueryEvaluator.h"

#include "../SPA/Utils/error/InvalidTokenException.h"
#include "../SPA/Utils/error/SyntaxError.h"
#include "../SPA/Utils/error/SemanticError.h"

using namespace std;

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
    if (wrapper == 0) wrapper = new TestWrapper;
    return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
    this->is_valid_source_ = true;
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
    SourceLexer lexer = SourceLexer(filename);
    std::shared_ptr<vector<SourceToken>> tokens;
    try {
        tokens = lexer.GetAllTokens();
    }
    catch (InvalidTokenException e) {
        std::cout << e.what() << std::endl;
        this->is_valid_source_ = false;
        return;
    }

    SourceValidator validator = SourceValidator();
    validator.SetTokens(tokens);
    if (validator.Validate()) {
        SourceParser parser = SourceParser();
        parser.SetTokens(tokens);
        std::shared_ptr<ProgramNode> root = parser.Parse();
        DesignExtractor extractor;
        extractor.PopulatePKB(root);
    } else {
        this->is_valid_source_ = false;
        cout << "\n\n***** Errors found in Source Code *****\n\n" << endl;
    }
}

// method to evaluating a query
void TestWrapper::Evaluate(std::string query_str, std::list<std::string>& results) {
    if (this->is_valid_source_) {
        QueryBuilder query_builder;
        std::shared_ptr<Query> query_ptr;
        try {
            query_ptr = query_builder.GetQuery(query_str);
        }
        catch (SyntaxError e) {
            std::cout << e.what() << std::endl;
            std::cout << "SyntaxError" << std::endl;
            results.push_back("SyntaxError");
            return;
        }
        catch (SemanticError e) {
            std::cout << e.what() << std::endl;
            results.push_back("SemanticError");
            return;
        }
        catch (...) {
            std::cout << "Unknown Exception" << endl;
        }

        cout << query_ptr->GetSelectTuple() << endl;
        QueryEvaluator evaluator(*query_ptr);
        evaluator.Evaluate();
        vector<std::string>& res = evaluator.ExtractResult();
        results.insert(results.end(), res.begin(), res.end());

        return;
    }
}