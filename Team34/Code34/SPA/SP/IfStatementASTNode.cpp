# include "IfStatementASTNode.h"

using namespace std;

void IfStatementASTNode::setIfChildren(std::vector<StatementASTNode>& if_c) {
	ifChildren = if_c;
}

std::vector<StatementASTNode> IfStatementASTNode::getIfChildren() {
	return ifChildren;
}

void IfStatementASTNode::setElseChildren(std::vector<StatementASTNode>& else_c) {
	elseChildren = else_c;
}

std::vector<StatementASTNode> IfStatementASTNode::getElseChildren() {
	return elseChildren;
}

void IfStatementASTNode::setConditionExpression(ConditionExpression& cond) {
	condition = cond;
}

ConditionExpression IfStatementASTNode::getCondition() {
	return condition;
}
