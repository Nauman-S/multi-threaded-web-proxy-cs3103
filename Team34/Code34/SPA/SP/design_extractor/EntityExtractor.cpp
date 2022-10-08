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

EntityExtractor::EntityExtractor(std::shared_ptr<WritePKBManager> manager): NodeExtractor(manager) {}

void EntityExtractor::ExtractProgramNode(const ProgramNode& program) {
	std::vector<std::shared_ptr<ProcedureASTNode>> children = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> child : children) {
		child->Extract(*this);
	}
}

void EntityExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
	this->write_manager_->AddProcedure(proc.GetProc());

	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void EntityExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {
	Variable lhs = assign.GetLeft();
	this->write_manager_->AddVariable(lhs);

	std::vector<Variable> rhs = assign.GetRightVars();
	for (Variable var : rhs) {
		this->write_manager_->AddVariable(var);
	}
	std::vector<Constant> consts = assign.GetRightCons();
	for (Constant con : consts) {
		this->write_manager_->AddConstant(con);
	}

	StmtNum line_no = assign.GetLineIndex();
	Expr expr = Expr(assign.GetInfix());
	this->write_manager_->AddAssignPattern(line_no, expr);
	this->write_manager_->AddStatement(line_no, RefType::kAssignRef);
}

void EntityExtractor::ExtractCallNode(const CallStatementASTNode& call) {
	StmtNum line_no = call.GetLineIndex();
	Procedure called_proc = call.GetProcedure();
	this->write_manager_->AddCallsStatement(called_proc, line_no);
	this->write_manager_->AddStatement(line_no, RefType::kCallRef);
}

void EntityExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {
	Variable var = print.GetVariable();
	this->write_manager_->AddVariable(var);

	StmtNum line_no = print.GetLineIndex();
	this->write_manager_->AddPrintStatement(var, line_no);
	this->write_manager_->AddStatement(line_no, RefType::kPrintRef);
}

void EntityExtractor::ExtractReadNode(const ReadStatementASTNode& read) {
	Variable var = read.GetReadVariable();
	this->write_manager_->AddVariable(var);

	StmtNum line_no = read.GetLineIndex();
	this->write_manager_->AddReadStatement(var, line_no);
	this->write_manager_->AddStatement(line_no, RefType::kReadRef);
}

void EntityExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
	StmtNum line_no = if_stmt.GetLineIndex();
	std::shared_ptr<ConditionExpression> cond = if_stmt.GetCondition();
	// Add variable pattern for if statements
	std::vector<Variable> vars = cond->GetVariables();
	for (Variable var : vars) {
		this->write_manager_->AddIfPattern(line_no, var);
	}
	cond->Extract(*this);

	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		else_child->Extract(*this);
	}

	this->write_manager_->AddStatement(line_no, RefType::kIfRef);
}

void EntityExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
	StmtNum line_no = while_stmt.GetLineIndex();
	std::shared_ptr<ConditionExpression> cond = while_stmt.GetCondition();
	// Add variable pattern for while statements
	std::vector<Variable> vars = cond->GetVariables();
	for (Variable var : vars) {
		this->write_manager_->AddWhilePattern(line_no, var);
	}
	cond->Extract(*this);

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}

	this->write_manager_->AddStatement(line_no, RefType::kWhileRef);
}

void EntityExtractor::ExtractConditionExpression(const ConditionExpression& cond) {
	std::vector<Variable> vars = cond.GetVariables();
	for (Variable var : vars) {
		this->write_manager_->AddVariable(var);
	}

	std::vector<Constant> consts = cond.GetConstants();
	for (Constant con : consts) {
		this->write_manager_->AddConstant(con);
	}
}
