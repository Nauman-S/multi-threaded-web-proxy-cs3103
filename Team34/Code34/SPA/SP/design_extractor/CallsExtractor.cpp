#include "../SourceParser.h"
#include "CallsExtractor.h"

CallsExtractor::CallsExtractor() {
	this->write_manager_ = WritePKBManager::GetInstance();
}

void CallsExtractor::ExtractProgramNode(ProgramNode& program) {
	std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> child : children) {
		child->Extract(*this);
	}
}

void CallsExtractor::ExtractProcedureNode(ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void CallsExtractor::ExtractCallNode(CallStatementASTNode& call) {
	Procedure parent_proc = call.GetParentProcIndex().GetName();
	Procedure called_proc = call.GetProcedure().GetName();
	// Add direct call from parent
	this->AddToCalls(parent_proc, called_proc);

	// Add indirect calls from call stacks
	this->procedure_calls_stack_.push_back(parent_proc);
	for (Procedure prev_proc : this->procedure_calls_stack_) {
		this->AddToCallsT(prev_proc, called_proc);
	}

	std::map<Procedure, std::shared_ptr<ProcedureASTNode>> name_to_node_map = SourceParser::proc_name_to_node_;
	std::shared_ptr<ProcedureASTNode> called_proc_node = name_to_node_map.at(called_proc);
	called_proc_node->Extract(*this);

	this->procedure_calls_stack_.pop_back();
}

void CallsExtractor::ExtractIfNode(IfStatementASTNode& if_stmt) {
	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		then_child->Extract(*this);
	}

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		else_child->Extract(*this);
	}
}
void CallsExtractor::ExtractWhileNode(WhileStatementASTNode& while_stmt) {
	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}
}

void CallsExtractor::ExtractAssignmentNode(AssignStatementASTNode& assign) {}
void CallsExtractor::ExtractPrintNode(PrintStatementASTNode& print) {}
void CallsExtractor::ExtractReadNode(ReadStatementASTNode& read) {}
void CallsExtractor::ExtractConditionExpression(ConditionExpression& cond) {}

void CallsExtractor::AddToCalls(Procedure caller, Procedure callee) {
	std::pair<Procedure, Procedure> calls = std::make_pair(caller, callee);
	if (this->added_calls_.find(calls) == this->added_calls_.end()) {
		this->write_manager_->SetCalls(caller, callee);
		this->added_calls_.insert(calls);
	}
}

void CallsExtractor::AddToCallsT(Procedure caller, Procedure callee) {
	std::pair<Procedure, Procedure> calls = std::make_pair(caller, callee);
	if (this->added_calls_T_.find(calls) == this->added_calls_T_.end()) {
		this->write_manager_->SetCallsT(caller, callee);
		this->added_calls_T_.insert(calls);
	}
}