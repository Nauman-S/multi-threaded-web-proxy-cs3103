#include "AssignStatementASTNode.h"

using namespace std;

void AssignStatementASTNode::SetLeft(Variable& l) {
	left = l;
}

void AssignStatementASTNode::SetRightVars(std::vector<Variable>& r) {
	right_vars = r;
}

void AssignStatementASTNode::SetRightCons(std::vector<Constant>& r) {
	right_cons = r;
}

Variable AssignStatementASTNode::GetLeft() {
	return left;
}

std::vector<Variable> AssignStatementASTNode::GetRightVars() {
	return right_vars;
}

std::vector<Constant> AssignStatementASTNode::GetRightCons() {
	return right_cons;
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
