#include "WhileStatementASTNode.h"

using namespace std;

void WhileStatementASTNode::setChildren(std::vector<StatementASTNode>& c) {
	children = c;
}

std::vector<StatementASTNode> WhileStatementASTNode::getChildren() {
	return children;
}

void WhileStatementASTNode::setConditionExpression(ConditionExpression& cond) {
	condition = cond;
}

ConditionExpression WhileStatementASTNode::getCondition() {
	return condition;
}