#include "ProcedureASTNode.h"

using namespace std;

ProcedureIndex ProcedureASTNode::getProc() {
	return proc;
}

std::vector<std::shared_ptr<StatementASTNode>> ProcedureASTNode::getChildren() {
	return children;
}

void ProcedureASTNode::setProc(ProcedureIndex& p) {
	proc = p;
}

void ProcedureASTNode::setChildren(std::vector<std::shared_ptr<StatementASTNode>>& chd) {
	children = chd;
}
