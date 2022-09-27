#pragma once

# include <vector>
# include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class ConditionExpression : public StatementASTNode {
public:
	void SetVariables(std::vector<Variable>&);

	std::vector<Variable> GetVariables();

	virtual void Extract(NodeExtractor&) override;

protected:
	std::vector<Variable> vars;
};