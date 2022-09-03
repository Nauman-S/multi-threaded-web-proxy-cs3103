#pragma once

# include "StatementASTNode.h"
# include "ConditionExpression.h"
# include <vector>

class WhileStatementASTNode : public StatementASTNode {
public:
	void setChildren(std::vector<StatementASTNode>&);

	std::vector<StatementASTNode> getChildren();

	void setConditionExpression(ConditionExpression&);

	ConditionExpression getCondition();

protected:
	ConditionExpression condition;
	std::vector<StatementASTNode> children;

};
