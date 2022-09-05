#include "TestWrapper.h"

#include <iostream>
#include <optional>
#include <map>

#include "../SPA/SP/SourceParser.h"
#include "../SPA/SP/DesignExtractor.h"

#include "../SPA/PKB/WritePKBManager.h"

#include "../SPA/QPS/parser/QueryBuilder.h"
#include "../SPA/QPS/parser/SyntaxError.h"
#include "../SPA/QPS/parser/SemanticError.h"
#include "../SPA/QPS/Query.h"
#include "../SPA/QPS/QueryEvaluator.h"
#include "../SPA/Utils/type/TypeDef.h"


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
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
    // ...rest of your code...
	SourceParser parser = SourceParser();
	ProgramNode node = parser.parse(filename);

	cout << "TEST" << endl;
	vector<ProcedureASTNode> p_nodes = node.getChildren();
	cout << "num of procedures: " << p_nodes.size() << endl;
	vector<StatementASTNode> s_nodes = p_nodes.at(0).getChildren();
	cout << "num of statements: " << s_nodes.size() << endl;

	DesignExtractor extractor = DesignExtractor();
	vector<int> consts = extractor.getConstants(filename);
	vector<VariableIndex> vars = extractor.getVariables(filename);
	vector<ProcedureIndex> procs = extractor.getProcedures(node);
	map<StatementASTNode, LineIndex> si_map = parser.si_mapping;
	map<LineIndex, StatementASTNode> is_map = parser.is_mapping;
	std::unique_ptr<WritePKBManager> pkb = WritePKBManager::GetInstance();
	map<StatementType, RefType> mapping;
	mapping.insert(pair<StatementType, RefType>(StatementType::sassign, RefType::kAssignRef));
	mapping.insert(pair<StatementType, RefType>(StatementType::sif, RefType::kIfRef));
	mapping.insert(pair<StatementType, RefType>(StatementType::sprint, RefType::kPrintRef));
	mapping.insert(pair<StatementType, RefType>(StatementType::sread, RefType::kReadRef));
	mapping.insert(pair<StatementType, RefType>(StatementType::swhile, RefType::kWhileRef));
	mapping.insert(pair<StatementType, RefType>(StatementType::scall, RefType::kCallRef));
	mapping.insert(pair<StatementType, RefType>(StatementType::sexpre, RefType::kStmtRef)); // need edit
	for (VariableIndex v : vars) {
		pkb->AddVariable(v.getName());
	}
	for (int c : consts) {
		pkb->AddConstant(Constant(c));
	}
	for (ProcedureIndex p : procs) {
		pkb->AddProcedure(Procedure(p.getName()));
	}

	for (pair<StatementASTNode, LineIndex> p : si_map) {
		pkb->AddStatement(p.second.getLineNum(), mapping[p.first.getStatementType()]);
	}
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query_str, std::list<std::string>& results){
    // call your evaluator to evaluate the query here
    // ...code to evaluate query...
	// store the answers to the query in the results list (it is initially empty)
	// each result must be a string.
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
	string res;
	if (evaluator.evaluate()) {
		res = evaluator.ExtractResult();
	}
	else {
		res = "none";
	}
	std::cout << res << std::endl;
	results.push_back(res);
	return;
    
}
