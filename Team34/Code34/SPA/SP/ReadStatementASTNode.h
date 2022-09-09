#pragma once

# include "StatementASTNode.h"
# include "VariableIndex.h"

class ReadStatementASTNode : public StatementASTNode {
public:
	void SetVariable(VariableIndex&);

	virtual VariableIndex GetReadVariable();

	virtual void Extract(NodeExtractor&) override;

protected:
	VariableIndex var;
};
