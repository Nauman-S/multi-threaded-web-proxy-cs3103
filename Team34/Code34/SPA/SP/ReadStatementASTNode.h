#pragma once

# include "StatementASTNode.h"
# include "VariableIndex.h"
# include "design_extractor/Extractable.h"
# include "design_extractor/NodeExtractor.h"

class ReadStatementASTNode : public StatementASTNode, public Extractable {
public:
	void setVariable(VariableIndex*);

	VariableIndex getVariable();

	virtual void Extract(NodeExtractor&);

protected:
	VariableIndex* var;
};
