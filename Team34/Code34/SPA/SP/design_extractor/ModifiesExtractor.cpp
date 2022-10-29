#include "ModifiesExtractor.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"

#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"

#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"
#include "../ast/ConditionExpression.h"

ModifiesExtractor::ModifiesExtractor(std::shared_ptr<WritePKBManager> manager) : NodeExtractor(manager) {}

void ModifiesExtractor::ExtractProgramNode(const ProgramNode& program) {
    this->proc_node_map_ = program.GetProcNodeMapping();
    std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
    for (shared_ptr<ProcedureASTNode> child : children) {
        child->Extract(*this);
    }
}

void ModifiesExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
    if (IsExtractedProcedure(proc.GetProc())) {
        return;
    }

    InitCachedSet(proc.GetProc());
    std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
    for (std::shared_ptr<StatementASTNode> child : children) {
        child->Extract(*this);
    }
}

/*
* Modifies: Variable on LHS of assignment
*/
void ModifiesExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {
    std::string proc_name = assign.GetParentProcIndex();
    int line_no = assign.GetLineIndex();

    Variable lhs = assign.GetLeft();
    this->AddToModifies(proc_name, lhs);
    this->AddToModifies(line_no, lhs);
    this->SetIndirectModifies(lhs);
}

void ModifiesExtractor::ExtractCallNode(const CallStatementASTNode& call) {
    Procedure parent_procedure = call.GetParentProcIndex();
    Procedure called_proc = call.GetProcedure();

    this->proc_call_stack_.push_back(parent_procedure);
    this->parent_smts_.push_back(call.GetLineIndex());

    if (IsExtractedProcedure(called_proc)) {
        // Set modifies from cached sets
        std::shared_ptr<std::set<Variable>> cached_modifies = this->proc_modifies_.at(called_proc);
        for (Variable modified_var : *cached_modifies) {
            this->SetIndirectModifies(modified_var);
        }
    }
    else {
        std::shared_ptr<ProcedureASTNode> called_proc_node = this->proc_node_map_.at(called_proc);
        called_proc_node->Extract(*this);
    }

    this->parent_smts_.pop_back();
    this->proc_call_stack_.pop_back();
}

void ModifiesExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {}

// Modifies: variable used by read
void ModifiesExtractor::ExtractReadNode(const ReadStatementASTNode& read) {
    Variable var = read.GetReadVariable();
    std::string proc_name = read.GetParentProcIndex();
    int line_no = read.GetLineIndex();

    this->AddToModifies(proc_name, var);
    this->AddToModifies(line_no, var);
    this->SetIndirectModifies(var);
}

void ModifiesExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
    std::shared_ptr<ConditionExpression> cond = if_stmt.GetCondition();
    cond->Extract(*this);

    // Remember parent container statement, and all modifies for children
    // will also apply for this container statement
    this->parent_smts_.push_back(if_stmt.GetLineIndex());
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

void ModifiesExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
    std::shared_ptr<ConditionExpression> cond = while_stmt.GetCondition();
    cond->Extract(*this);

    this->parent_smts_.push_back(while_stmt.GetLineIndex());
    std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
    for (std::shared_ptr<StatementASTNode> child : children) {
        child->Extract(*this);
    }
    this->parent_smts_.pop_back();
}

void ModifiesExtractor::ExtractConditionExpression(const ConditionExpression& cond) {}

bool ModifiesExtractor::IsExtractedProcedure(Procedure p) {
    return this->proc_modifies_.find(p) != this->proc_modifies_.end();
}

void ModifiesExtractor::InitCachedSet(Procedure p) {
    std::shared_ptr<std::set<Variable>> modifies_set(new std::set<Variable>());
    this->proc_modifies_.insert(std::make_pair(p, modifies_set));
}

// Sets modifies on the variable for parent procedure calls and container stmts
void ModifiesExtractor::SetIndirectModifies(Variable var) {
    for (Procedure p : this->proc_call_stack_) {
        this->AddToModifies(p, var);
    }
    for (StmtNum l : this->parent_smts_) {
        this->AddToModifies(l, var);
    }
}

void ModifiesExtractor::AddToModifies(StmtNum line, Variable var) {
    this->write_manager_->SetModifies(line, var);
}

void ModifiesExtractor::AddToModifies(Procedure proc, Variable var) {
    this->write_manager_->SetModifies(proc, var);
    std::shared_ptr<std::set<Variable>> cached_set = this->proc_modifies_.at(proc);
    cached_set->insert(var);
}
