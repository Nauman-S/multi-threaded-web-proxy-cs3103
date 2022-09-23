#include "CallStatementASTNode.h"

using namespace std;

void CallStatementASTNode::SetProcedure(ProcedureIndex& p) {
	proc = p;
}

ProcedureIndex CallStatementASTNode::GetProcedure() {
	return proc;
}

void CallStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractCallNode(*this);
}

