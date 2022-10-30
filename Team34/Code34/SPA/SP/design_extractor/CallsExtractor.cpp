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
    if (IsExtractedProcedure(proc.GetProc())) {
        return;
    }

    InitCachedSet(proc.GetProc());
    std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
    for (std::shared_ptr<StatementASTNode> child : children) {
        child->Extract(*this);
    }
    // At this point, the set of Calls* for proc is fully populated. 
    std::shared_ptr<std::set<Procedure>> populated_set = this->proc_to_calls_T_.at(proc.GetProc());
    for (Procedure p : *populated_set) {
        this->AddToCallsT(proc.GetProc(), p);
    }
}

void CallsExtractor::ExtractCallNode(const CallStatementASTNode& call) {
    Procedure parent_proc = call.GetParentProcIndex();
    Procedure called_proc = call.GetProcedure();
    // Add direct call from parent
    this->AddToCalls(parent_proc, called_proc);

    // Add indirect calls from call stacks
    this->procedure_calls_stack_.push_back(parent_proc);
    this->AddToCachedSet(called_proc);

    if (IsExtractedProcedure(called_proc)) {
        // Add Calls* relation through cached set instead of reevaluating procedure node
        std::shared_ptr<std::set<Procedure>> cached_set = this->proc_to_calls_T_.at(called_proc);
        for (Procedure p : *cached_set) {
            this->AddToCachedSet(p);
        }
    } else {
        // Jump to called node and extract that first
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

bool CallsExtractor::IsExtractedProcedure(Procedure p) {
    return this->proc_to_calls_T_.find(p) != this->proc_to_calls_T_.end();
}

void CallsExtractor::AddToCachedSet(Procedure called) {
    for (Procedure prev_proc : this->procedure_calls_stack_) {
        std::shared_ptr<std::set<Procedure>> cached_set = this->proc_to_calls_T_.at(prev_proc);
        cached_set->insert(called);
    }
}

void CallsExtractor::InitCachedSet(Procedure p) {
    std::shared_ptr<std::set<Procedure>> new_set(new std::set<Procedure>());
    this->proc_to_calls_T_.insert(std::make_pair(p, new_set));
}

void CallsExtractor::AddToCalls(Procedure caller, Procedure callee) {
    this->write_manager_->SetCalls(caller, callee);
}

void CallsExtractor::AddToCallsT(Procedure caller, Procedure callee) {
    this->write_manager_->SetCallsT(caller, callee);
}
