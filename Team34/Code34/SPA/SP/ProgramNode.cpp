#include "ProgramNode.h"

using namespace std;

std::list<ProcedureASTNode> ProgramNode::getChildren() {
	return *children;
}

void ProgramNode::setChildren(std::list<ProcedureASTNode>* c) {
	children = c;
}