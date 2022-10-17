#include "CallsExtractor.h"

CallsExtractor::CallsExtractor(std::shared_ptr<WritePKBManager> manager) : NodeExtractor(manager) {}

void CallsExtractor::ExtractProgramNode(const ProgramNode& program) {
    this->proc_node_map_ = program.GetProcNodeMapping();
    std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
    for (shared_ptr<ProcedureASTNode> child : children) {
        child->Extract(*this);
    }
}

void CallsExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
    std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
    for (std::shared_ptr<StatementASTNode> child : children) {
        child->Extract(*this);
    }
}

void CallsExtractor::ExtractCallNode(const CallStatementASTNode& call) {
    Procedure parent_proc = call.GetParentProcIndex();
    Procedure called_proc = call.GetProcedure();
    // Add direct call from parent
    this->AddToCalls(parent_proc, called_proc);

    // Add indirect calls from call stacks
    this->procedure_calls_stack_.push_back(parent_proc);
    for (Procedure prev_proc : this->procedure_calls_stack_) {
        this->AddToCallsT(prev_proc, called_proc);
    }

    if (this->proc_node_map_.find(called_proc) != this->proc_node_map_.end()) {
        std::shared_ptr<ProcedureASTNode> called_proc_node = this->proc_node_map_.at(called_proc);
        called_proc_node->Extract(*this);
    }

    this->procedure_calls_stack_.pop_back();
}

void CallsExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
    std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
    for (std::shared_ptr<StatementASTNode> then_child : then_children) {
        then_child->Extract(*this);
    }

    std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
    for (std::shared_ptr<StatementASTNode> else_child : else_children) {
        else_child->Extract(*this);
    }
}
void CallsExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
    std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
    for (std::shared_ptr<StatementASTNode> child : children) {
        child->Extract(*this);
    }
}

void CallsExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {}
void CallsExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {}
void CallsExtractor::ExtractReadNode(const ReadStatementASTNode& read) {}
void CallsExtractor::ExtractConditionExpression(const ConditionExpression& cond) {}

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
