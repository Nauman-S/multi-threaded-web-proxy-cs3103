#pragma once

#include <memory>
#include <vector>

#include "NodeExtractor.h"

#include "../../PKB/WritePKBManager.h"
#include "../../Utils/type/TypeDef.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"
#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"
#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"
#include "../ast/ConditionExpression.h"

class ParentsExtractor : public NodeExtractor {
public:

	ParentsExtractor();

	virtual void ExtractProgramNode(ProgramNode&) override;
	virtual void ExtractProcedureNode(ProcedureASTNode&) override;

	virtual void ExtractAssignmentNode(AssignStatementASTNode&) override;
	virtual void ExtractCallNode(CallStatementASTNode&) override;
	virtual void ExtractPrintNode(PrintStatementASTNode&) override;
	virtual void ExtractReadNode(ReadStatementASTNode&) override;

	virtual void ExtractIfNode(IfStatementASTNode&) override;
	virtual void ExtractWhileNode(WhileStatementASTNode&) override;
	virtual void ExtractConditionExpression(ConditionExpression&) override;

private:
	std::unique_ptr<WritePKBManager> write_manager_;
	// Keeps track of parent statements in previous level as we go down
	// in nesting level
	std::vector<StmtNum> previous_parents_;

	void AddIndirectParents(StmtNum);
};
