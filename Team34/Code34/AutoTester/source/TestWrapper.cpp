#include "TestWrapper.h"

#include <iostream>
#include <optional>
#include <memory>
#include <map>

#include "../SPA/SP/SourceParser.h"
#include "../SPA/SP/DesignExtractor.h"
#include "../SPA/SP/tokenizer/SourceLexer.h"
#include "../SPA/SP/SourceValidator.h"
#include "../SPA/QPS/parser/QueryBuilder.h"
#include "../SPA/QPS/parser/SyntaxError.h"
#include "../SPA/QPS/parser/SemanticError.h"
#include "../SPA/QPS/Query.h"
#include "../SPA/QPS/QueryEvaluator.h"

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
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
    // ...rest of your code...
	SourceLexer lexer = SourceLexer(filename);
	vector<SourceToken> tokens = lexer.GetAllTokens();
	SourceValidator validator = SourceValidator();
	if (validator.Validate(tokens)) {
 		SourceParser parser = SourceParser();
		std::shared_ptr<ProgramNode> root = parser.Parse(filename);
		DesignExtractor extractor;
		extractor.PopulatePKB(root);
		extractor.AddConstants(filename);
	}
	else {
		this->is_valid_source_ = false;
	    cout << "Errors found in Source Code" << endl;
	}
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query_str, std::list<std::string>& results){
    // call your evaluator to evaluate the query here
    // ...code to evaluate query...
	// store the answers to the query in the results list (it is initially empty)
	// each result must be a string.
	if (this->is_valid_source_) {
		QueryBuilder q_builder;
		Query query;

		try {
			std::shared_ptr<Query> query_ptr = q_builder.GetQuery(query_str);
			query = *query_ptr;
		}
		catch (SyntaxError e) {
			std::cout << e.what() << std::endl;
			std::cout << "SyntaxError" << std::endl;
			results.push_back("SyntaxError");
			return;
		}
		catch (SemanticError) {
			std::cout << "SemanticError" << std::endl;
			results.push_back("SemanticError");
			return;
		}
		catch (...) {
			std::cout << "Unknown Exception" << endl;
		}

		cout << query.GetSelectTuple() << endl;
		QueryEvaluator evaluator(query);
		if (evaluator.evaluate()) {
			vector<std::string> res = evaluator.ExtractResult();
			results.insert(results.end(), res.begin(), res.end());
		}
		//std::cout << res << std::endl;
		//results.push_back(res);
		return;
	}
}
