#pragma once

# include "StatementASTNode.h"
# include "../ProcedureIndex.h"

class CallStatementASTNode : public StatementASTNode {
public:
	void SetProcedure(ProcedureIndex& p);

	ProcedureIndex GetProcedure();

	virtual void Extract(NodeExtractor&) override;

protected:
	ProcedureIndex proc;
};
