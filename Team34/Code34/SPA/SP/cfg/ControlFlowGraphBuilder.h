#pragma once

#include "ControlFlowNode.h"
#include "../ast/ProcedureASTNode.h"


class ControlFlowGraphBuilder {
public:
	static ControlFlowNode GenerateCFG(ProcedureASTNode);
};