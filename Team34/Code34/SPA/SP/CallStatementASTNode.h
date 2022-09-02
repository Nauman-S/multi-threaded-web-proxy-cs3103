#pragma once

# include "StatementASTNode.h"
# include "ProcedureIndex.h"

class CallStatementASTNode : public StatementASTNode {
public:
	void setProcedure(ProcedureIndex& p);

	ProcedureIndex getProcedure();

protected:
	ProcedureIndex proc;
};
