#include "AssignStatementASTNode.h"

using namespace std;

void AssignStatementASTNode::setLeft(VariableIndex& l) {
	left = l;
}

void AssignStatementASTNode::setRight(std::vector<VariableIndex>& r) {
	right = r;
}

VariableIndex AssignStatementASTNode::getLeft() {
	return left;
}

std::vector<VariableIndex> AssignStatementASTNode::getRight() {
	return right;
}