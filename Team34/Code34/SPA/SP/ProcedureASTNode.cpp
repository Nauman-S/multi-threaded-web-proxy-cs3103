#include "ProcedureASTNode.h"

using namespace std;

std::string ProcedureASTNode::getName() {
	return name;
}

std::list<StatementASTNode> ProcedureASTNode::getChildren() {
	return *children;
}

void ProcedureASTNode::setName(std::string n) {
	name = name;
}

void ProcedureASTNode::setChildren(std::list<StatementASTNode>* chd) {
	children = chd;
}
