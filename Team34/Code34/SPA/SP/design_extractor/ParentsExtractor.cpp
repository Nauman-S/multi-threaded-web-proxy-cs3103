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
	for (int parent_s : this->previous_parents_) {
		//
		this->parents_star.push_back(std::make_pair(parent_s, assign.GetLineIndex().GetLineNum()));
		//
	}
}

void ParentsExtractor::ExtractCallNode(CallStatementASTNode& call) {
	// TODO: Traversing procedure within procedure
}

void ParentsExtractor::ExtractPrintNode(PrintStatementASTNode& print) {
	for (int parent_s : this->previous_parents_) {
		//
		this->parents_star.push_back(std::make_pair(parent_s, print.GetLineIndex().GetLineNum()));
		//
	}
}

void ParentsExtractor::ExtractReadNode(ReadStatementASTNode& read) {
	for (int parent_s : this->previous_parents_) {
		//
		this->parents_star.push_back(std::make_pair(parent_s, read.GetLineIndex().GetLineNum()));
		//
	}
}

void ParentsExtractor::ExtractIfNode(IfStatementASTNode& if_stmt) {
	for (int parent_s : this->previous_parents_) {
		//
		this->parents_star.push_back(std::make_pair(parent_s, if_stmt.GetLineIndex().GetLineNum()));
		//
	}

	int parent_line = if_stmt.GetLineIndex().GetLineNum();

	this->previous_parents_.push_back(parent_line);
	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		int child_line = then_child->GetLineIndex().GetLineNum();
		//
		this->parents.push_back(std::make_pair(parent_line, child_line));
		//
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		int child_line = else_child->GetLineIndex().GetLineNum();
		//
		this->parents.push_back(std::make_pair(parent_line, child_line));
		//
		else_child->Extract(*this);
	}
	this->previous_parents_.pop_back();
}

void ParentsExtractor::ExtractWhileNode(WhileStatementASTNode& while_stmt) {
	for (int parent_s : this->previous_parents_) {
		//
		this->parents_star.push_back(std::make_pair(parent_s, while_stmt.GetLineIndex().GetLineNum()));
		//
	}

	int parent_line = while_stmt.GetLineIndex().GetLineNum();
	this->previous_parents_.push_back(parent_line);

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		int child_line = child->GetLineIndex().GetLineNum();
		//
		this->parents.push_back(std::make_pair(parent_line, child_line));
		//
		child->Extract(*this);
	}

	this->previous_parents_.pop_back();
}

void ParentsExtractor::ExtractConditionExpression(ConditionExpression& cond) {}
