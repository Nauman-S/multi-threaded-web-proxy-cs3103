#pragma once

#include <memory>
#include <set>
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

	std::vector<Procedure> proc_call_stack_;
	std::vector<StmtNum> parent_smts_;

	std::set<std::pair<StmtNum, Variable>> stmt_uses_cache_;
	std::set<std::pair<Procedure, Variable>> procedure_uses_cache_;

	std::set<std::pair<StmtNum, Variable>> stmt_modifies_cache_;
	std::set<std::pair<Procedure, Variable>> procedure_modifies_cache_;

	void SetUses(StmtNum, Variable);
	void SetUses(Procedure, Variable);

	void SetModifies(StmtNum, Variable);
	void SetModifies(Procedure, Variable);

	void SetIndirectUses(Variable);
	void SetIndirectModifies(Variable);
};

