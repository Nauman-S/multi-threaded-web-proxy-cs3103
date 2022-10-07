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
	UsesModifiesExtractor(std::shared_ptr<WritePKBManager>);

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
	std::map<Procedure, std::shared_ptr<ProcedureASTNode>> proc_node_map_;

	// Cached add of uses relationship
	std::set<std::pair<StmtNum, Variable>> stmt_uses_cache_;
	std::set<std::pair<Procedure, Variable>> procedure_uses_cache_;
	void AddToUses(StmtNum, Variable);
	void AddToUses(Procedure, Variable);

	// Cached add of modifies relationship
	std::set<std::pair<StmtNum, Variable>> stmt_modifies_cache_;
	std::set<std::pair<Procedure, Variable>> procedure_modifies_cache_;
	void AddToModifies(StmtNum, Variable);
	void AddToModifies(Procedure, Variable);

	// Add uses and modifies relationship from indirect parents (container
	// and call statements)
	std::vector<Procedure> proc_call_stack_;
	std::vector<StmtNum> parent_smts_;
	void SetIndirectUses(Variable);
	void SetIndirectModifies(Variable);
};

