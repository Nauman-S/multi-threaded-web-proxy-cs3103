#pragma once
#include "../ast/ProcedureASTNode.h"
#include "ControlFlowNode.h"
#include "../tokenizer/SourceToken.h"

class CFGBuilder {
public:
	map<Procedure, shared_ptr<ControlFlowNode>> GenerateCFG(std::string& source_filename);

	map<StmtNum, shared_ptr<ControlFlowNode>> GetMapping();

	void Display(shared_ptr<ControlFlowNode>, set<set<StmtNum>>&);

protected:
	pair<Procedure, shared_ptr<ControlFlowNode>> GenerateProcedureCFG(std::shared_ptr<std::vector<SourceToken>>, int&, int&);

	shared_ptr<ControlFlowNode> GenerateStatementCFG(std::shared_ptr<std::vector<SourceToken>>, int&, int&, shared_ptr<ControlFlowNode>);

	shared_ptr<ControlFlowNode> GenerateSimpleCFG(std::shared_ptr<std::vector<SourceToken>>, int&, int&, shared_ptr<ControlFlowNode>);

	shared_ptr<ControlFlowNode> GenerateWhileCFG(std::shared_ptr<std::vector<SourceToken>>, int&, int&, shared_ptr<ControlFlowNode>);

	shared_ptr<ControlFlowNode> GenerateIfCFG(std::shared_ptr<std::vector<SourceToken>>, int&, int&, shared_ptr<ControlFlowNode>);

	map<StmtNum, shared_ptr<ControlFlowNode>> mapping;
};