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
	std::vector<std::shared_ptr<ProcedureASTNode>> children = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> child : children) {
		child->Extract(*this);
	}
}

void EntityExtractor::ExtractProcedureNode(ProcedureASTNode& proc) {
	this->write_manager_->AddProcedure(proc.GetProc().GetName());

	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void EntityExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {
	int line_no = assign.GetLineIndex().GetLineNum();

	std::vector<VariableIndex> rhs = assign.GetRight();
	for (VariableIndex var : rhs) {
		this->write_manager_->AddVariable(var.GetName());
	}
	VariableIndex lhs = assign.GetLeft();
	this->write_manager_->AddVariable(lhs.GetName());

	Expr expr = Expr(assign.GetInfix());
	this->write_manager_->AddAssignPattern(line_no, lhs.GetName(), expr);

	this->write_manager_->AddStatement(line_no, RefType::kAssignRef);
}

void EntityExtractor::ExtractCallNode(CallStatementASTNode& call) {
	int line_no = call.GetLineIndex().GetLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kCallRef);
}

void EntityExtractor::ExtractPrintNode(PrintStatementASTNode& print) {
	VariableIndex var = print.GetVariable();
	this->write_manager_->AddVariable(var.GetName());

	int line_no = print.GetLineIndex().GetLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kPrintRef);
}

void EntityExtractor::ExtractReadNode(ReadStatementASTNode& read) {
	VariableIndex var = read.GetReadVariable();
	this->write_manager_->AddVariable(var.GetName());

	int line_no = read.GetLineIndex().GetLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kReadRef);
}

void EntityExtractor::ExtractIfNode(IfStatementASTNode& if_stmt) {
	std::shared_ptr<ConditionExpression> cond = if_stmt.GetCondition();
	cond->Extract(*this);

	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		else_child->Extract(*this);
	}

	int line_no = if_stmt.GetLineIndex().GetLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kIfRef);
}

void EntityExtractor::ExtractWhileNode(WhileStatementASTNode& while_stmt) {
	std::shared_ptr<ConditionExpression> cond = while_stmt.GetCondition();
	cond->Extract(*this);

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}

	int line_no = while_stmt.GetLineIndex().GetLineNum();
	this->write_manager_->AddStatement(line_no, RefType::kWhileRef);
}

void EntityExtractor::ExtractConditionExpression(ConditionExpression& cond) {
	//TODO: Check if variable in condition statement should be added
	// Is variable not declared previously considered invalid to appear
	// in cond expression? or should we add regardlessly as a variable
	std::vector<VariableIndex> vars = cond.GetVariables();
	for (VariableIndex var : vars) {
		this->write_manager_->AddVariable(var.GetName());
	}
}
