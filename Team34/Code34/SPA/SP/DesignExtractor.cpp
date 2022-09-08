#include "DesignExtractor.h"
# include "SourceLexer.h"
# include <vector>
# include "SourceToken.h"

using namespace std;

vector<int> DesignExtractor::GetConstants(std::string &sourcefile) {
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

vector<VariableIndex> DesignExtractor::GetVariables(std::string& sourcefile) {
	vector<VariableIndex> vars;
	SourceLexer lexer = SourceLexer(sourcefile);
	vector<SourceToken> tokens = lexer.GetAllTokens();
	int idx = 0;
	while (idx < (int) tokens.size()) {
		if (tokens.at(idx).GetType() == SourceTokenType::kProcedure) {
			idx += 2;
		}
		else if (tokens.at(idx).GetType() == SourceTokenType::kName) {
			VariableIndex v = VariableIndex();
			v.SetName(tokens.at(idx).GetStringVal());
			vars.push_back(v);
			idx += 1;
		}
		else {
			idx += 1;
		}
	}
	return vars;
}

vector<ProcedureIndex> DesignExtractor::GetProcedures(std::shared_ptr<ProgramNode> node) {
	vector<ProcedureIndex> procs;
	vector<shared_ptr<ProcedureASTNode>> children = node->GetChildren();
	for (shared_ptr<ProcedureASTNode> proc : children) {
		procs.push_back(proc->GetProc());
	}
	return procs;
}