#include "ParentsExtractor.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"

#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"

#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"
#include "../ast/ConditionExpression.h"

ParentsExtractor::ParentsExtractor(std::shared_ptr<WritePKBManager> manager): NodeExtractor(manager) {}

void ParentsExtractor::ExtractProgramNode(const ProgramNode& program) {
	std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> child : children) {
		child->Extract(*this);
	}
}

void ParentsExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void ParentsExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {
	this->AddIndirectParents(assign.GetLineIndex());
}

void ParentsExtractor::ExtractCallNode(const CallStatementASTNode& call) {
	this->AddIndirectParents(call.GetLineIndex());
}

void ParentsExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {
	this->AddIndirectParents(print.GetLineIndex());
}

void ParentsExtractor::ExtractReadNode(const ReadStatementASTNode& read) {
	this->AddIndirectParents(read.GetLineIndex());
}

void ParentsExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
	this->AddIndirectParents(if_stmt.GetLineIndex());

	StmtNum parent_line = if_stmt.GetLineIndex();
	// Store statement num of container statement, for indirect child to refer
	this->previous_parents_.push_back(parent_line);

	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		StmtNum child_line = then_child->GetLineIndex();
		this->write_manager_->SetParent(parent_line, child_line);
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		StmtNum child_line = else_child->GetLineIndex();
		this->write_manager_->SetParent(parent_line, child_line);
		else_child->Extract(*this);
	}
	// On backtrack, remove container statement
	this->previous_parents_.pop_back();
}

void ParentsExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
	this->AddIndirectParents(while_stmt.GetLineIndex());

	int parent_line = while_stmt.GetLineIndex();
	this->previous_parents_.push_back(parent_line);

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		StmtNum child_line = child->GetLineIndex();
		this->write_manager_->SetParent(parent_line, child_line);
		child->Extract(*this);
	}

	this->previous_parents_.pop_back();
}

void ParentsExtractor::ExtractConditionExpression(const ConditionExpression& cond) {}

void ParentsExtractor::AddIndirectParents(StmtNum current) {
	for (StmtNum parent : this->previous_parents_) {
		this->write_manager_->SetParentT(parent, current);
	}
}
