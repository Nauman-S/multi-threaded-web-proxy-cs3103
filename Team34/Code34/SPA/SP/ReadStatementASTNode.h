#pragma once

# include "StatementASTNode.h"
# include "VariableIndex.h"

class ReadStatementASTNode : public StatementASTNode {
public:
	void setVariable(VariableIndex&);

	virtual VariableIndex getReadVariable();

protected:
	VariableIndex var;
};
