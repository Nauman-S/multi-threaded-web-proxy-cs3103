#pragma once

# include <vector>
# include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class ConditionExpression : public StatementASTNode {
public:
	void SetVariables(std::vector<Variable>&);

	void SetConstants(std::vector<Constant>&);

	std::vector<Variable> GetVariables();

	std::vector<Constant> GetConstants();

	virtual void Extract(NodeExtractor&) override;

protected:
	std::vector<Variable> vars;
	std::vector<Constant> cons;
};