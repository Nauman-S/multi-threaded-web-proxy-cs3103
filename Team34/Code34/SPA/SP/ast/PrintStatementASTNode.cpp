# include "PrintStatementASTNode.h"

using namespace std;

void PrintStatementASTNode::SetVariable(VariableIndex& v) {
	var = v;
}

VariableIndex PrintStatementASTNode::GetVariable() {
	return var;
}

void PrintStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractPrintNode(*this);
}
