#include "ParentsExtractor.h"

#include "../ProgramNode.h"
#include "../ProcedureASTNode.h"

#include "../AssignStatementASTNode.h"
#include "../CallStatementASTNode.h"
#include "../PrintStatementASTNode.h"
#include "../ReadStatementASTNode.h"

#include "../IfStatementASTNode.h"
#include "../WhileStatementASTNode.h"
#include "../ConditionExpression.h"

ParentsExtractor::ParentsExtractor() {
	this->write_manager_ = WritePKBManager::GetInstance();
}

void ParentsExtractor::ExtractProgramNode(ProgramNode& program) {
	std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> child : children) {
		child->Extract(*this);
	}
}

void ParentsExtractor::ExtractProcedureNode(ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void ParentsExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {
	this->AddIndirectParents(assign.GetLineIndex().GetLineNum());
}

void ParentsExtractor::ExtractCallNode(CallStatementASTNode& call) {
	this->AddIndirectParents(call.GetLineIndex().GetLineNum());
}

void ParentsExtractor::ExtractPrintNode(PrintStatementASTNode& print) {
	this->AddIndirectParents(print.GetLineIndex().GetLineNum());
}

void ParentsExtractor::ExtractReadNode(ReadStatementASTNode& read) {
	this->AddIndirectParents(read.GetLineIndex().GetLineNum());
}

void ParentsExtractor::ExtractIfNode(IfStatementASTNode& if_stmt) {
	this->AddIndirectParents(if_stmt.GetLineIndex().GetLineNum());

	StmtNum parent_line = if_stmt.GetLineIndex().GetLineNum();
	// Store statement num of container statement, for indirect child to refer
	this->previous_parents_.push_back(parent_line);

	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		StmtNum child_line = then_child->GetLineIndex().GetLineNum();
		this->write_manager_->SetParent(parent_line, child_line);
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		StmtNum child_line = else_child->GetLineIndex().GetLineNum();
		this->write_manager_->SetParent(parent_line, child_line);
		else_child->Extract(*this);
	}
	// On backtrack, remove container statement
	this->previous_parents_.pop_back();
}

void ParentsExtractor::ExtractWhileNode(WhileStatementASTNode& while_stmt) {
	this->AddIndirectParents(while_stmt.GetLineIndex().GetLineNum());

	int parent_line = while_stmt.GetLineIndex().GetLineNum();
	this->previous_parents_.push_back(parent_line);

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		StmtNum child_line = child->GetLineIndex().GetLineNum();
		this->write_manager_->SetParent(parent_line, child_line);
		child->Extract(*this);
	}

	this->previous_parents_.pop_back();
}

void ParentsExtractor::ExtractConditionExpression(ConditionExpression& cond) {}

void ParentsExtractor::AddIndirectParents(StmtNum current) {
	for (StmtNum parent : this->previous_parents_) {
		this->write_manager_->SetParentS(parent, current);
	}
}
