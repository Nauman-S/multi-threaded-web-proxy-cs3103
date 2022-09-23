#pragma once

#include <memory>
#include <vector>

#include "StatementASTNode.h"
#include "ConditionExpression.h"

class IfStatementASTNode : public StatementASTNode {
public:
	void SetIfChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	std::vector<std::shared_ptr<StatementASTNode>> GetIfChildren();

	void SetElseChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	std::vector<std::shared_ptr<StatementASTNode>> GetElseChildren();

	void SetConditionExpression(std::shared_ptr<ConditionExpression>);

	std::shared_ptr<ConditionExpression> GetCondition();

	virtual void Extract(NodeExtractor&) override;

protected:
	std::shared_ptr<ConditionExpression> condition;
	std::vector<std::shared_ptr<StatementASTNode>> ifChildren;
	std::vector<std::shared_ptr<StatementASTNode>> elseChildren;
};
