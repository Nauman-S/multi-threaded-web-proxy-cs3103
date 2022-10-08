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

Variable AssignStatementASTNode::GetLeft() const {
	return left;
}

std::vector<Variable> AssignStatementASTNode::GetRightVars() const {
	return right_vars;
}

std::vector<Constant> AssignStatementASTNode::GetRightCons() const {
	return right_cons;
}

void AssignStatementASTNode::SetInfix(string& s) {
	infix = s;
}

string AssignStatementASTNode::GetInfix() const {
	return infix;
}

void AssignStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractAssignmentNode(*this);
}
