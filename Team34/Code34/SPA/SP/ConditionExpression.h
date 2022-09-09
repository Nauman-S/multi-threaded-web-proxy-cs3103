#pragma once

# include <vector>
# include "StatementASTNode.h"


class ConditionExpression : public StatementASTNode {
public:
	void SetVariables(std::vector<VariableIndex>&);

	std::vector<VariableIndex> GetVariables();

	virtual void Extract(NodeExtractor&) override;

	void SetPostfix(std::string);

protected:
	std::vector<VariableIndex> vars;
	std::string postfix;
};