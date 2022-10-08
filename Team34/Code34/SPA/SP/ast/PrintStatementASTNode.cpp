# include "PrintStatementASTNode.h"

using namespace std;

void PrintStatementASTNode::SetVariable(Variable& v) {
	var = v;
}

Variable PrintStatementASTNode::GetVariable() const {
	return var;
}

void PrintStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractPrintNode(*this);
}
