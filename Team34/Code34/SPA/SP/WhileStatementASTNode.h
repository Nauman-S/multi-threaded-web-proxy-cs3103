#pragma once

# include "StatementASTNode.h"
# include "ProcedureIndex.h"
# include "ConditionExpression.h"

class WhileStatementASTNode : public StatementASTNode {
public:
	void setChildren(StatementASTNode[] chd) {
		children = chd;
	}

	StatementASTNode[] getChildren() {
		return children;
	}

	void setConditionExpression(ConditionExpression cond) {
		condition = cond;
	}

	ConditionExpression getCondition() {
		return condition;
	}

protected:
	ConditionExpression condition;
	StatementASTNode[] children;

};
