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

	ParentsExtractor(std::shared_ptr<WritePKBManager>);

	virtual void ExtractProgramNode(const ProgramNode&) override;
	virtual void ExtractProcedureNode(const ProcedureASTNode&) override;

	virtual void ExtractAssignmentNode(const AssignStatementASTNode&) override;
	virtual void ExtractCallNode(const CallStatementASTNode&) override;
	virtual void ExtractPrintNode(const PrintStatementASTNode&) override;
	virtual void ExtractReadNode(const ReadStatementASTNode&) override;

	virtual void ExtractIfNode(const IfStatementASTNode&) override;
	virtual void ExtractWhileNode(const WhileStatementASTNode&) override;
	virtual void ExtractConditionExpression(const ConditionExpression&) override;

private:
	// Keeps track of parent statements in previous level as we go down
	// in nesting level
	std::vector<StmtNum> previous_parents_;

	void AddIndirectParents(StmtNum);
};
