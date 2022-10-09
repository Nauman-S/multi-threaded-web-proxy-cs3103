#include "NextExtractor.h"

#include <cassert>

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"

#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"
#include "../ast/ConditionExpression.h"

#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"

NextExtractor::NextExtractor(std::shared_ptr<WritePKBManager> manager): NodeExtractor(manager) {}

void NextExtractor::ExtractProgramNode(const ProgramNode& program) {
	std::vector<shared_ptr<ProcedureASTNode>> procedures = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> proc : procedures) {
		this->ClearPrevStmts(); // Clear stored statements from previous procedures
		proc->Extract(*this);
	}
}

void NextExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> stmts = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> stmt : stmts) {
		stmt->Extract(*this);
	}
}

void NextExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {
	StmtNum line = assign.GetLineIndex();
	this->AddNextRelation(line);
	this->ClearPrevStmts();
	this->AddStmtToPrev(line);
}

void NextExtractor::ExtractCallNode(const CallStatementASTNode& call) {
	StmtNum line = call.GetLineIndex();
	this->AddNextRelation(line);
	this->ClearPrevStmts();
	this->AddStmtToPrev(line);
}

void NextExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {
	StmtNum line = print.GetLineIndex();
	this->AddNextRelation(line);
	this->ClearPrevStmts();
	this->AddStmtToPrev(line);
}

void NextExtractor::ExtractReadNode(const ReadStatementASTNode& read) {
	StmtNum line = read.GetLineIndex();
	this->AddNextRelation(line);
	this->ClearPrevStmts();
	this->AddStmtToPrev(line);
}

void NextExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
	StmtNum parent_line = if_stmt.GetLineIndex();
	this->AddNextRelation(parent_line);

	this->ClearPrevStmts();
	this->AddStmtToPrev(parent_line);
	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		then_child->Extract(*this);
	}
	std::set<StmtNum> prev_from_if_branch = this->prev_stmts_;

	this->ClearPrevStmts();
	this->AddStmtToPrev(parent_line);
	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		else_child->Extract(*this);
	}
	std::set<StmtNum> prev_from_else_branch = this->prev_stmts_;

	// Combine statement numbers from both if and else branches, as both will
	// be previous to the statement right after this if statement
	this->ClearPrevStmts();
	for (StmtNum num : prev_from_if_branch) {
		this->AddStmtToPrev(num);
	}
	for (StmtNum num : prev_from_else_branch) {
		this->AddStmtToPrev(num);
	}
}

void NextExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
	StmtNum parent_line = while_stmt.GetLineIndex();
	this->AddNextRelation(parent_line);
	this->ClearPrevStmts();
	this->AddStmtToPrev(parent_line);

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
	this->AddNextRelation(parent_line);

	// Previous statements on leaving a while node should contain 
	// only the while container
	this->ClearPrevStmts();
	this->AddStmtToPrev(parent_line);
}

void NextExtractor::ExtractConditionExpression(const ConditionExpression& cond) {}

void NextExtractor::AddStmtToPrev(StmtNum num) {
	this->prev_stmts_.insert(num);
}

void NextExtractor::ClearPrevStmts() {
	this->prev_stmts_.clear();
}

// Populate Next relationship directly from prev and next statement numbers
void NextExtractor::AddNextRelation(StmtNum prev, StmtNum next) {
	this->write_manager_->SetNext(prev, next);
}

// Populate Next relationship from set of previous statements
void NextExtractor::AddNextRelation(StmtNum current) {
	for (StmtNum prev : this->prev_stmts_) {
		this->write_manager_->SetNext(prev, current);
	}
}

