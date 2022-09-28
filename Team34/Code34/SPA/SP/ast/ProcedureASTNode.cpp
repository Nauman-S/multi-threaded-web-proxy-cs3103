#include "ProcedureASTNode.h"

using namespace std;

Procedure ProcedureASTNode::GetProc() {
	return proc;
}

std::vector<std::shared_ptr<StatementASTNode>> ProcedureASTNode::GetChildren() {
	return children;
}

void ProcedureASTNode::SetProc(Procedure& p) {
	proc = p;
}

void ProcedureASTNode::SetChildren(std::vector<std::shared_ptr<StatementASTNode>>& chd) {
	children = chd;
}

void ProcedureASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractProcedureNode(*this);
}

