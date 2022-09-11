#pragma once

#include <memory>
#include <set>
#include <vector>

#include "NodeExtractor.h"

#include "../../PKB/WritePKBManager.h"
#include "../../Utils/type/TypeDef.h"

#include "../ProgramNode.h"
#include "../ProcedureASTNode.h"
#include "../AssignStatementASTNode.h"
#include "../CallStatementASTNode.h"
#include "../PrintStatementASTNode.h"
#include "../ReadStatementASTNode.h"
#include "../IfStatementASTNode.h"
#include "../WhileStatementASTNode.h"
#include "../ConditionExpression.h"

class UsesModifiesExtractor : public NodeExtractor {
public:
	UsesModifiesExtractor();

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

	std::set<Procedure> extracted_proc_;
	std::vector<Procedure> proc_call_stack_;

	bool IsExtractedProcedure(Procedure);
	void SetIndirectUses(Variable);
	void SetIndirectModifies(Variable);
};

