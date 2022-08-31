#pragma once

# include "StatementASTNode.h"
# include "ProcedureIndex.h"
# include "ConditionExpression.h"
# include <list>

class WhileStatementASTNode : public StatementASTNode {
public:
	void setChildren(list<StatementASTNode>* c) {
		children = c;
	}

	list<StatementASTNode> getChildren() {
		return *children;
	}

	void setConditionExpression(ConditionExpression *cond) {
		condition = cond;
	}

	ConditionExpression getCondition() {
		return *condition;
	}

protected:
	ConditionExpression* condition;
	StatementASTNode<list>* children;

};
