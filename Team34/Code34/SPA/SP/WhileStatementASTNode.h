#pragma once

#include <vector>
#include <memory>

#include "StatementASTNode.h"
#include "ConditionExpression.h"

class WhileStatementASTNode : public StatementASTNode {
public:
	void setChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	std::vector<std::shared_ptr<StatementASTNode>> getChildren();

	void setConditionExpression(std::shared_ptr<ConditionExpression>);

	std::shared_ptr<ConditionExpression> getCondition();

protected:
	std::shared_ptr<ConditionExpression> condition;
	std::vector<std::shared_ptr<StatementASTNode>> children;

};
