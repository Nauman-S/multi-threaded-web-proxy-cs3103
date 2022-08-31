#pragma once

# include "StatementASTNode.h"
# include "ProcedureIndex.h"

class CallStatementASTNode : public StatementASTNode {
public:
	void seProcedure(ProcedureIndex p) {
		proc = p;
	}

	ProcedureIndex getProcedure() {
		return proc;
	}

protected:
	ProcedureIndex proc;
};
