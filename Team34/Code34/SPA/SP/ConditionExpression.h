#pragma once
# include "StatementASTNode.h"
# include <vector>

class ConditionExpression : public StatementASTNode {
public:
	void setVariables(std::vector<VariableIndex>&);

	std::vector<VariableIndex> getVariables();

	virtual void Extract(NodeExtractor&) override;

protected:
	std::vector<VariableIndex> vars;
};