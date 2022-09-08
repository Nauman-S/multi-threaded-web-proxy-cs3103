#pragma once

# include "StatementASTNode.h"
# include "VariableIndex.h"

class PrintStatementASTNode : public StatementASTNode {
public:
	void SetVariable(VariableIndex&);

	VariableIndex GetVariable();

	virtual void Extract(NodeExtractor&) override;

protected:
	VariableIndex var;
};
