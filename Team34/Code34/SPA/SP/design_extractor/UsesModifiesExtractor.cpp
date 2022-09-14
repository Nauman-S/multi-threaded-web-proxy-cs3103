#include "UsesModifiesExtractor.h"

#include "..\SourceParser.h"

#include "../ProgramNode.h"
#include "../ProcedureASTNode.h"

#include "../AssignStatementASTNode.h"
#include "../CallStatementASTNode.h"
#include "../PrintStatementASTNode.h"
#include "../ReadStatementASTNode.h"

#include "../IfStatementASTNode.h"
#include "../WhileStatementASTNode.h"
#include "../ConditionExpression.h"

UsesModifiesExtractor::UsesModifiesExtractor() {
	this->write_manager_ = WritePKBManager::GetInstance();
}

void UsesModifiesExtractor::ExtractProgramNode(ProgramNode& program) {
	std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> child : children) {
		child->Extract(*this);
	}
}

void UsesModifiesExtractor::ExtractProcedureNode(ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

/*
* Uses: All variables on RHS of assignment
* Modifies: Variable on LHS of assignment
*/
void UsesModifiesExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {
	std::string proc_name = assign.GetParentProcIndex().GetName();
	int line_no = assign.GetLineIndex().GetLineNum();

	std::vector<VariableIndex> rhs = assign.GetRight();
	for (VariableIndex var : rhs) {
		this->write_manager_->SetUses(proc_name, var.GetName());
		this->write_manager_->SetUses(line_no, var.GetName());
		this->SetIndirectUses(var.GetName());
	}

	VariableIndex lhs = assign.GetLeft();
	this->write_manager_->SetModifies(proc_name, lhs.GetName());
	this->write_manager_->SetModifies(line_no, lhs.GetName());
	this->SetIndirectModifies(lhs.GetName());
}

void UsesModifiesExtractor::ExtractCallNode(CallStatementASTNode& call) {
	std::map<Procedure, std::shared_ptr<ProcedureASTNode>> name_to_node_map = SourceParser::proc_name_to_node_;
	Procedure proc_name = call.GetProcedure().GetName();
	if (name_to_node_map.find(proc_name) == name_to_node_map.end()) {
		// Consider if should return error when calling undefined procedure
		return;
	}

	Procedure parent_procedure = call.GetParentProcIndex().GetName();
	std::shared_ptr<ProcedureASTNode> called_proc_node = name_to_node_map.at(proc_name);
	this->proc_call_stack_.push_back(parent_procedure);
	this->parent_smts_.push_back(call.GetLineIndex().GetLineNum());
	called_proc_node->Extract(*this);
	this->parent_smts_.pop_back();
	this->proc_call_stack_.pop_back();
}

// Uses: variable used by print
void UsesModifiesExtractor::ExtractPrintNode(PrintStatementASTNode& print) {
	VariableIndex var = print.GetVariable();
	std::string proc_name = print.GetParentProcIndex().GetName();
	int line_no = print.GetLineIndex().GetLineNum();

	this->write_manager_->SetUses(proc_name, var.GetName());
	this->write_manager_->SetUses(line_no, var.GetName());
	this->SetIndirectUses(var.GetName());
}

// Modifies: variable used by read
void UsesModifiesExtractor::ExtractReadNode(ReadStatementASTNode& read) {
	VariableIndex var = read.GetReadVariable();
	std::string proc_name = read.GetParentProcIndex().GetName();
	int line_no = read.GetLineIndex().GetLineNum();

	this->write_manager_->SetModifies(proc_name, var.GetName());
	this->write_manager_->SetModifies(line_no, var.GetName());
	this->SetIndirectModifies(var.GetName());
}

void UsesModifiesExtractor::ExtractIfNode(IfStatementASTNode& if_stmt) {
	std::shared_ptr<ConditionExpression> cond = if_stmt.GetCondition();
	cond->Extract(*this);

	// Remember parent container statement, and all UsesModifies for children
	// will also apply for this container statement
	this->parent_smts_.push_back(if_stmt.GetLineIndex().GetLineNum());
	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		else_child->Extract(*this);
	}
	this->parent_smts_.pop_back();
}

void UsesModifiesExtractor::ExtractWhileNode(WhileStatementASTNode& while_stmt) {
	std::shared_ptr<ConditionExpression> cond = while_stmt.GetCondition();
	cond->Extract(*this);

	this->parent_smts_.push_back(while_stmt.GetLineIndex().GetLineNum());
	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
	this->parent_smts_.pop_back();
}

// Uses: all variables involved in a conditional expression
void UsesModifiesExtractor::ExtractConditionExpression(ConditionExpression& cond) {
	std::string proc_name = cond.GetParentProcIndex().GetName();
	int line_no = cond.GetLineIndex().GetLineNum();

	std::vector<VariableIndex> vars = cond.GetVariables();
	for (VariableIndex var : vars) {
		this->write_manager_->SetUses(line_no, var.GetName());
		this->write_manager_->SetUses(proc_name, var.GetName());
		this->SetIndirectUses(var.GetName());
	}
}

// Sets uses on the variable for parent procedure calls and container stmts
void UsesModifiesExtractor::SetIndirectUses(Variable var) {
	for (Procedure p : this->proc_call_stack_) {
		this->write_manager_->SetUses(p, var);
	}
	for (StmtNum l : this->parent_smts_) {
		this->write_manager_->SetUses(l, var);
	}
}

// Sets modifies on the variable for parent procedure calls and container stmts
void UsesModifiesExtractor::SetIndirectModifies(Variable var) {
	for (Procedure p : this->proc_call_stack_) {
		this->write_manager_->SetModifies(p, var);
	}
	for (StmtNum l : this->parent_smts_) {
		this->write_manager_->SetModifies(l, var);
	}
}
