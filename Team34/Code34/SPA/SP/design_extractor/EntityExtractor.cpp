#include "EntityExtractor.h"

#include "../ProgramNode.h"
#include "../ProcedureASTNode.h"

#include "../AssignStatementASTNode.h"
#include "../CallStatementASTNode.h"
#include "../PrintStatementASTNode.h"
#include "../ReadStatementASTNode.h"

#include "../IfStatementASTNode.h"
#include "../WhileStatementASTNode.h"
#include "../ConditionExpression.h"

#include "../../Utils/type/RefType.h"

EntityExtractor::EntityExtractor() {
	this->write_manager_ = WritePKBManager::GetInstance();
}

void EntityExtractor::ExtractProgramNode(ProgramNode& program) {
	std::vector<ProcedureASTNode> children = program.getChildren();
	for (ProcedureASTNode child : children) {
		child.Extract(*this);
	}
}

void EntityExtractor::ExtractProcedureNode(ProcedureASTNode& proc) {
	this->write_manager_->AddProcedure(proc.getProc().getName());

	std::vector<std::shared_ptr<StatementASTNode>> children = proc.getChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void EntityExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {
	std::vector<VariableIndex> rhs = assign.getRight();
	for (VariableIndex var : rhs) {
		this->write_manager_->AddVariable(var.getName());
	}
	VariableIndex lhs = assign.getLeft();
	this->write_manager_->AddVariable(lhs.getName());

	int line_no = assign.getLineIndex().getLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kAssignRef);
}

void EntityExtractor::ExtractCallNode(CallStatementASTNode& call) {
	int line_no = call.getLineIndex().getLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kCallRef);
}

void EntityExtractor::ExtractPrintNode(PrintStatementASTNode& print) {
	VariableIndex var = print.getVariable();
	this->write_manager_->AddVariable(var.getName());

	int line_no = print.getLineIndex().getLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kPrintRef);
}

void EntityExtractor::ExtractReadNode(ReadStatementASTNode& read) {
	VariableIndex var = read.getReadVariable();
	this->write_manager_->AddVariable(var.getName());

	int line_no = read.getLineIndex().getLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kReadRef);
}

void EntityExtractor::ExtractIfNode(IfStatementASTNode& if_stmt) {
	std::shared_ptr<ConditionExpression> cond = if_stmt.getCondition();
	cond->Extract(*this);

	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.getIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.getElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		else_child->Extract(*this);
	}

	int line_no = if_stmt.getLineIndex().getLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kIfRef);
}

void EntityExtractor::ExtractWhileNode(WhileStatementASTNode& while_stmt) {
	std::shared_ptr<ConditionExpression> cond = while_stmt.getCondition();
	cond->Extract(*this);

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.getChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}

	int line_no = while_stmt.getLineIndex().getLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kWhileRef);
}

void EntityExtractor::ExtractConditionExpression(ConditionExpression& cond) {
	//TODO: Check if variable in condition statement should be added
	// Is variable not declared previously considered invalid to appear
	// in cond expression? or should we add regardlessly as a variable
	std::vector<VariableIndex> vars = cond.getVariables();
	for (VariableIndex var : vars) {
		this->write_manager_->AddVariable(var.getName());
	}
}
