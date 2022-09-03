#include "ProcedureASTNode.h"

using namespace std;

std::string ProcedureASTNode::getName() {
	return name;
}

std::vector<StatementASTNode> ProcedureASTNode::getChildren() {
	return children;
}

void ProcedureASTNode::setName(std::string n) {
	name = name;
}

void ProcedureASTNode::setChildren(std::vector<StatementASTNode>& chd) {
	children = chd;
}
