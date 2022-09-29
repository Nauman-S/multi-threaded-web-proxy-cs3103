#include "EntityExtractor.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"

#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"

#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"
#include "../ast/ConditionExpression.h"

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
	this->write_manager_->AddProcedure(proc.GetProc());

	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void EntityExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {
	int line_no = assign.GetLineIndex();

	std::vector<Variable> rhs = assign.GetRightVars();
	for (Variable var : rhs) {
		this->write_manager_->AddVariable(var);
	}
	Variable lhs = assign.GetLeft();
	this->write_manager_->AddVariable(lhs);

	Expr expr = Expr(assign.GetInfix());
	this->write_manager_->AddAssignPattern(line_no, expr);

	this->write_manager_->AddStatement(line_no, RefType::kAssignRef);
}

void EntityExtractor::ExtractCallNode(CallStatementASTNode& call) {
	int line_no = call.GetLineIndex();
	this->write_manager_->AddStatement(line_no, RefType::kCallRef);
}

void EntityExtractor::ExtractPrintNode(PrintStatementASTNode& print) {
	Variable var = print.GetVariable();
	this->write_manager_->AddVariable(var);

	int line_no = print.GetLineIndex();
	this->write_manager_->AddStatement(line_no, RefType::kPrintRef);
}

void EntityExtractor::ExtractReadNode(ReadStatementASTNode& read) {
	Variable var = read.GetReadVariable();
	this->write_manager_->AddVariable(var);

	int line_no = read.GetLineIndex();
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

	int line_no = if_stmt.GetLineIndex();
	this->write_manager_->AddStatement(line_no, RefType::kIfRef);
}

void EntityExtractor::ExtractWhileNode(WhileStatementASTNode& while_stmt) {
	std::shared_ptr<ConditionExpression> cond = while_stmt.GetCondition();
	cond->Extract(*this);

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}

	int line_no = while_stmt.GetLineIndex();
	this->write_manager_->AddStatement(line_no, RefType::kWhileRef);
}

void EntityExtractor::ExtractConditionExpression(ConditionExpression& cond) {
	//TODO: Check if variable in condition statement should be added
	// Is variable not declared previously considered invalid to appear
	// in cond expression? or should we add regardlessly as a variable
	std::vector<Variable> vars = cond.GetVariables();
	for (Variable var : vars) {
		this->write_manager_->AddVariable(var);
	}
}
