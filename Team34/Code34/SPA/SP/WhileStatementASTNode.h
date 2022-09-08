#pragma once

#include <vector>
#include <memory>

#include "StatementASTNode.h"
#include "ConditionExpression.h"

class WhileStatementASTNode : public StatementASTNode {
public:
	void SetChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	std::vector<std::shared_ptr<StatementASTNode>> GetChildren();

	void SetConditionExpression(std::shared_ptr<ConditionExpression>);

	std::shared_ptr<ConditionExpression> GetCondition();

	virtual void Extract(NodeExtractor&) override;

protected:
	std::shared_ptr<ConditionExpression> condition;
	std::vector<std::shared_ptr<StatementASTNode>> children;
};
