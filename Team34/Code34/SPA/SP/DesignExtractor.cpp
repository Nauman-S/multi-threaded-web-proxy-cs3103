#include "DesignExtractor.h"
# include "SourceLexer.h"
# include <vector>
# include "SourceToken.h"

using namespace std;

vector<int> DesignExtractor::getConstants(std::string &sourcefile) {
	vector<int> consts;
	SourceLexer lexer = SourceLexer(sourcefile);
	vector<SourceToken> tokens = lexer.GetAllTokens();
	for (SourceToken t : tokens) {
		if (t.GetType() == SourceTokenType::kInteger) {
			int c = stoi(t.GetStringVal());
			consts.push_back(c);
		}
	}
	return consts;
}

vector<VariableIndex> DesignExtractor::getVariables(std::string& sourcefile) {
	vector<VariableIndex> vars;
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
			vars.push_back(v);
			idx += 1;
		}
		else {
			idx += 1;
		}
	}
	return vars;
}

vector<ProcedureIndex> DesignExtractor::getProcedures(ProgramNode node) {
	vector<ProcedureIndex> procs;
	vector<ProcedureASTNode> children = node.getChildren();
	for (ProcedureASTNode proc : children) {
		procs.push_back(proc.getProc());
	}
	return procs;
}