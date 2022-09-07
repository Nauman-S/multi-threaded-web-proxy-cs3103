#include "UsesModifiesExtractor.h"

#include "../ProgramNode.h"
#include "../ProcedureASTNode.h"
#include "../AssignStatementASTNode.h"
#include "../PrintStatementASTNode.h"
#include "../ReadStatementASTNode.h"

UsesModifiesExtractor::UsesModifiesExtractor() {
	this->write_manager_ = WritePKBManager::GetInstance();
}

void UsesModifiesExtractor::ExtractProgramNode(ProgramNode& program) {
	std::vector<ProcedureASTNode> children = program.getChildren();
	for (ProcedureASTNode child : children) {
		child.Extract(*this);
	}
}

void UsesModifiesExtractor::ExtractProcedureNode(ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> children = proc.getChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

/*
* Uses: All variables on RHS of assignment
* Modifies: Variable on LHS of assignment
*/
void UsesModifiesExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {
	int line_no = assign.getLineIndex().getLineNum();

	std::vector<VariableIndex> rhs = assign.getRight();
	for (VariableIndex var : rhs) {
		this->write_manager_->SetUses(line_no, var.getName());
	}

	VariableIndex lhs = assign.getLeft();
	this->write_manager_->SetModifies(line_no, lhs.getName());
}

// Uses: variable used by print
void UsesModifiesExtractor::ExtractPrintNode(PrintStatementASTNode& print) {
	VariableIndex var = print.getVariable();
	int line_no = print.getLineIndex().getLineNum();
	this->write_manager_->SetUses(line_no, var.getName());
}

// Modifies: variable used by read
void UsesModifiesExtractor::ExtractReadNode(ReadStatementASTNode& read) {
	VariableIndex var = read.getReadVariable();
	int line_no = read.getLineIndex().getLineNum();
	this->write_manager_->SetModifies(line_no, var.getName());
}
