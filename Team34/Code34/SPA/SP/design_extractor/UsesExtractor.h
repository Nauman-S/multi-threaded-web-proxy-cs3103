#pragma once

#include <memory>

#include "NodeExtractor.h"

#include "../ProgramNode.h"
#include "../ProcedureASTNode.h"
#include "../AssignStatementASTNode.h"
#include "../PrintStatementASTNode.h"
#include "../ReadStatementASTNode.h"

#include "../../PKB/WritePKBManager.h"

class UsesExtractor : public NodeExtractor {
public:
	std::unique_ptr<WritePKBManager> write_manager_;

	UsesExtractor();

	virtual void ExtractProgramNode(ProgramNode&);
	virtual void ExtractProcedureNode(ProcedureASTNode&);
	virtual void ExtractAssignmentNode(AssignStatementASTNode&);
	virtual void ExtractPrintNode(PrintStatementASTNode&);
	virtual void ExtractReadNode(ReadStatementASTNode&);
};
