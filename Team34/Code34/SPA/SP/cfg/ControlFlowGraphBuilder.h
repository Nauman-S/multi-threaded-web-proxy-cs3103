#pragma once

#include "ControlFlowNode.h"
#include "../ast/ProcedureASTNode.h"


class ControlFlowGraphBuilder {
public:
	ControlFlowNode GenerateCFG(ProcedureASTNode&);

	void SingleHandler(ControlFlowNode*, StatementASTNode&);

	void WhileHandler(ControlFlowNode*, StatementASTNode&);

	void IfHandler(ControlFlowNode*, StatementASTNode&);
};