#pragma once

# include "StatementASTNode.h"
# include "ProcedureIndex.h"

class CallStatementASTNode : public StatementASTNode {
public:
	void setProcedure(ProcedureIndex& p);

	ProcedureIndex getProcedure();

	virtual void Extract(NodeExtractor&) override;

protected:
	ProcedureIndex proc;
};
