#include "ProgramNode.h"

using namespace std;

std::vector<ProcedureASTNode> ProgramNode::getChildren() {
	return children;
}

void ProgramNode::setChildren(std::vector<ProcedureASTNode>& c) {
	children = c;
}