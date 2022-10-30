#pragma once

#include <vector>
#include <memory>
#include <string>

#include "StatementASTNode.h"
#include "ConditionExpression.h"

class WhileStatementASTNode : public StatementASTNode {
public:
    void SetChildren(std::vector<std::shared_ptr<StatementASTNode>>&);
    std::vector<std::shared_ptr<StatementASTNode>> GetChildren() const;

    void SetConditionExpression(std::shared_ptr<ConditionExpression>);
    std::shared_ptr<ConditionExpression> GetCondition() const;

    void Extract(NodeExtractor&) override;
    string Stringify() override;

protected:
    std::shared_ptr<ConditionExpression> condition;
    std::vector<std::shared_ptr<StatementASTNode>> children;
};
