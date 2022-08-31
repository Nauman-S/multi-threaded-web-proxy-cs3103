#include "WhileStatementASTNode.h"

using namespace std;

void WhileStatementASTNode::setChildren(std::list<StatementASTNode>* c) {
	children = c;
}

std::list<StatementASTNode> WhileStatementASTNode::getChildren() {
	return *children;
}

void WhileStatementASTNode::setConditionExpression(ConditionExpression* cond) {
	condition = cond;
}

ConditionExpression WhileStatementASTNode::getCondition() {
	return *condition;
}