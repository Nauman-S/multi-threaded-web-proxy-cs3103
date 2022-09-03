#include "ProcedureASTNode.h"

using namespace std;

ProcedureIndex ProcedureASTNode::getProc() {
	return proc;
}

std::vector<StatementASTNode> ProcedureASTNode::getChildren() {
	return children;
}

void ProcedureASTNode::setProc(ProcedureIndex& p) {
	proc = p;
}

void ProcedureASTNode::setChildren(std::vector<StatementASTNode>& chd) {
	children = chd;
}
