#include "WhileStatementASTNode.h"

using namespace std;

void setChildren(list<StatementASTNode>* c) {
	children = c;
}

list<StatementASTNode> getChildren() {
	return *children;
}

void setConditionExpression(ConditionExpression* cond) {
	condition = cond;
}

ConditionExpression getCondition() {
	return *condition;
}