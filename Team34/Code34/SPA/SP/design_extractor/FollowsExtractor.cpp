#include "FollowsExtractor.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"

#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"
#include "../ast/ConditionExpression.h"

#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"

FollowsExtractor::FollowsExtractor(std::shared_ptr<WritePKBManager> manager): NodeExtractor(manager) {}

void FollowsExtractor::ExtractProgramNode(const ProgramNode& program) {
	std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> child : children) {
		child->Extract(*this);
	}
}

void FollowsExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	this->AddFollowsRelation(children);
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void FollowsExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {}

void FollowsExtractor::ExtractCallNode(const CallStatementASTNode& call) {}

void FollowsExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {}

void FollowsExtractor::ExtractReadNode(const ReadStatementASTNode& read) {}

void FollowsExtractor::ExtractConditionExpression(const ConditionExpression& cond) {}

void FollowsExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	this->AddFollowsRelation(then_children);
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	this->AddFollowsRelation(else_children);
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		else_child->Extract(*this);
	}
}

void FollowsExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	this->AddFollowsRelation(children);
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}


// Populate both Follows and Follows* relation in given stmt list
void FollowsExtractor::AddFollowsRelation(const std::vector<std::shared_ptr<StatementASTNode>> stmts) {
	if (stmts.empty()) {
		return;
	}

	std::vector<StmtNum> previous_lines;
	StmtNum prev = stmts[0]->GetLineIndex();
	previous_lines.push_back(prev);

	for (unsigned int i = 1; i < stmts.size(); i++) {
		StmtNum current = stmts[i]->GetLineIndex();
		this->write_manager_->SetFollows(prev, current);
		for (StmtNum line : previous_lines) {
			this->write_manager_->SetFollowsT(line, current);
		}

		previous_lines.push_back(current);
		prev = current;
	}
}
