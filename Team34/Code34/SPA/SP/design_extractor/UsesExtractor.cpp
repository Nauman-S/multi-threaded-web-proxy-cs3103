#include "UsesExtractor.h"

#include "../ProgramNode.h"
#include "../ProcedureASTNode.h"
#include "../AssignStatementASTNode.h"
#include "../PrintStatementASTNode.h"
#include "../ReadStatementASTNode.h"

UsesExtractor::UsesExtractor() {
	this->write_manager_ = WritePKBManager::GetInstance();
}

void UsesExtractor::ExtractProgramNode(ProgramNode& program) {
	std::vector<ProcedureASTNode> children = program.getChildren();
	for (ProcedureASTNode child : children) {
		child.Extract(*this);
	}
}

void UsesExtractor::ExtractProcedureNode(ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> children = proc.getChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

// Uses: RHS of an assignment statement
void UsesExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {
	std::vector<VariableIndex> rhs = assign.getRight();
	int line_no = assign.getLineIndex().getLineNum();
	for (VariableIndex var : rhs) {
		this->write_manager_->SetUses(line_no, var.getName());
	}
}

// Uses: variable used by print
void UsesExtractor::ExtractPrintNode(PrintStatementASTNode& print) {
	VariableIndex var = print.getVariable();
	int line_no = print.getLineIndex().getLineNum();
	this->write_manager_->SetUses(line_no, var.getName());
}

void UsesExtractor::ExtractReadNode(ReadStatementASTNode& read) {}

