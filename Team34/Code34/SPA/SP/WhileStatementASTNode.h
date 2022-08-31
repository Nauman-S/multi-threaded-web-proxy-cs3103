#pragma once

# include "StatementASTNode.h"
# include "ProcedureIndex.h"
# include "ConditionExpression.h"
# include <list>

class WhileStatementASTNode : public StatementASTNode {
public:
	void setChildren(std::list<StatementASTNode>*);

	std::list<StatementASTNode> getChildren();

	void setConditionExpression(ConditionExpression*);

	ConditionExpression getCondition();

protected:
	ConditionExpression* condition;
	std::list<StatementASTNode>* children;

};
