#pragma once

# include "StatementASTNode.h"
# include "VariableIndex.h"

class PrintStatementASTNode : public StatementASTNode {
public:
	void setVariable(VariableIndex&);

	VariableIndex getVariable();

	virtual void Extract(NodeExtractor&) override;

protected:
	VariableIndex var;
};
