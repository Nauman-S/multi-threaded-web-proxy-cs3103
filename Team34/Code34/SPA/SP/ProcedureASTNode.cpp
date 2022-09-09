#include "ProcedureASTNode.h"

using namespace std;

ProcedureIndex ProcedureASTNode::GetProc() {
	return proc;
}

std::vector<std::shared_ptr<StatementASTNode>> ProcedureASTNode::GetChildren() {
	return children;
}

void ProcedureASTNode::SetProc(ProcedureIndex& p) {
	proc = p;
}

void ProcedureASTNode::SetChildren(std::vector<std::shared_ptr<StatementASTNode>>& chd) {
	children = chd;
}

void ProcedureASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractProcedureNode(*this);
}

