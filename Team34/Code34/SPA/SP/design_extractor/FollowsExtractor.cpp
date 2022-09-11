#include "FollowsExtractor.h"

#include "../ProgramNode.h"
#include "../ProcedureASTNode.h"

#include "../AssignStatementASTNode.h"
#include "../CallStatementASTNode.h"
#include "../PrintStatementASTNode.h"
#include "../ReadStatementASTNode.h"
#include "../ConditionExpression.h"

#include "../IfStatementASTNode.h"
#include "../WhileStatementASTNode.h"

FollowsExtractor::FollowsExtractor() {
	this->write_manager_ = WritePKBManager::GetInstance();
}

void FollowsExtractor::ExtractProgramNode(ProgramNode& program) {
	std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> child : children) {
		child->Extract(*this);
	}
}

void FollowsExtractor::ExtractProcedureNode(ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	this->AddFollowsRelation(children);
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void FollowsExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {}

void FollowsExtractor::ExtractCallNode(CallStatementASTNode& call) {}

void FollowsExtractor::ExtractPrintNode(PrintStatementASTNode& print) {}

void FollowsExtractor::ExtractReadNode(ReadStatementASTNode& read) {}

void FollowsExtractor::ExtractConditionExpression(ConditionExpression& cond) {}

void FollowsExtractor::ExtractIfNode(IfStatementASTNode& if_stmt) {
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

void FollowsExtractor::ExtractWhileNode(WhileStatementASTNode& while_stmt) {
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
	StmtNum prev = stmts[0]->GetLineIndex().GetLineNum();
	previous_lines.push_back(prev);

	for (int i = 1; i < stmts.size(); i++) {
		StmtNum current = stmts[i]->GetLineIndex().GetLineNum();
		this->write_manager_->SetFollows(prev, current);
		for (StmtNum line : previous_lines) {
			this->write_manager_->SetFollowsT(line, current);
		}

		previous_lines.push_back(current);
		prev = current;
	}
}
