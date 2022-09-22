#include "AssignStatementASTNode.h"

using namespace std;

void AssignStatementASTNode::SetLeft(VariableIndex& l) {
	left = l;
}

void AssignStatementASTNode::SetRight(std::vector<VariableIndex>& r) {
	right = r;
}

VariableIndex AssignStatementASTNode::GetLeft() {
	return left;
}

std::vector<VariableIndex> AssignStatementASTNode::GetRight() {
	return right;
}

void AssignStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractAssignmentNode(*this);
}

void AssignStatementASTNode::SetInfix(string& s) {
	infix = s;
}

string AssignStatementASTNode::GetInfix() {
	return infix;
}
