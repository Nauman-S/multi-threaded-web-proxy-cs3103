#pragma once

# include "StatementASTNode.h"
# include "VariableIndex.h"

class ReadStatementASTNode : public StatementASTNode {
public:
	void setVariable(VariableIndex v) {
		var = v;
	}

	VariableIndex getVariable() {
		return var;
	}

protected:
	VariableIndex var;
};
