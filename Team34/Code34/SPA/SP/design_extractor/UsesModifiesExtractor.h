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

