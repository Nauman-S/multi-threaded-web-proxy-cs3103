#pragma once

# include "StatementASTNode.h"
# include "ConditionExpression.h"
# include <vector>

class IfStatementASTNode : public StatementASTNode {
public:
	void setIfChildren(std::vector<StatementASTNode>&);

	std::vector<StatementASTNode> getIfChildren();

	void setElseChildren(std::vector<StatementASTNode>&);

	std::vector<StatementASTNode> getElseChildren();

	void setConditionExpression(ConditionExpression&);

	ConditionExpression getCondition();

protected:
	ConditionExpression condition;
	std::vector<StatementASTNode> ifChildren;
	std::vector<StatementASTNode> elseChildren;
};
