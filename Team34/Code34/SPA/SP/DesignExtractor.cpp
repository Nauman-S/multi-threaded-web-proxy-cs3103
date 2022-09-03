#include "DesignExtractor.h"
# include "SourceLexer.h"
# include <vector>
# include "SourceToken.h"

using namespace std;

ConstantManager DesignExtractor::getConstants(std::string &sourcefile) {
	ConstantManager manager = ConstantManager();
	SourceLexer lexer = SourceLexer(sourcefile);
	vector<SourceToken> tokens = lexer.GetAllTokens();
	for (SourceToken t : tokens) {
		if (t.GetType() == SourceTokenType::kInteger) {
			int c = stoi(t.GetStringVal());
			manager.addConstant(c);
		}
	}
	return manager;
}

VariableManager DesignExtractor::getVariables(std::string& sourcefile) {
	VariableManager manager = VariableManager();
	SourceLexer lexer = SourceLexer(sourcefile);
	vector<SourceToken> tokens = lexer.GetAllTokens();
	int idx = 0;
	while (idx < tokens.size()) {
		if (tokens.at(idx).GetType() == SourceTokenType::kProcedure) {
			idx += 2;
		}
		else if (tokens.at(idx).GetType() == SourceTokenType::kName) {
			VariableIndex v = VariableIndex();
			v.setName(tokens.at(idx).GetStringVal());
			manager.addVariable(v);
			idx += 1;
		}
		else {
			idx += 1;
		}
	}
	return manager;
}

ProcedureManager DesignExtractor::getProcedures(ProgramNode node) {
	ProcedureManager manager = ProcedureManager();
	vector<ProcedureASTNode> children = node.getChildren();
	for (ProcedureASTNode proc : children) {
		manager.addProcedure(proc.getProc());
	}
	return manager;
}