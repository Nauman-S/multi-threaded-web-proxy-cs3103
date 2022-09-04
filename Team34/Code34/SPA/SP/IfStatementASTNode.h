#pragma once

#include <memory>
#include <vector>

#include "StatementASTNode.h"
#include "ConditionExpression.h"

class IfStatementASTNode : public StatementASTNode {
public:
	void setIfChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	std::vector<std::shared_ptr<StatementASTNode>> getIfChildren();

	void setElseChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	std::vector<std::shared_ptr<StatementASTNode>> getElseChildren();

	void setConditionExpression(std::shared_ptr<ConditionExpression>);

	std::shared_ptr<ConditionExpression> getCondition();

protected:
	std::shared_ptr<ConditionExpression> condition;
	std::vector<std::shared_ptr<StatementASTNode>> ifChildren;
	std::vector<std::shared_ptr<StatementASTNode>> elseChildren;
};
