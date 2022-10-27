#include "UsesExtractor.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"

#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"

#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"
#include "../ast/ConditionExpression.h"

UsesExtractor::UsesExtractor(std::shared_ptr<WritePKBManager> manager) : NodeExtractor(manager) {}

void UsesExtractor::ExtractProgramNode(const ProgramNode& program) {
    this->proc_node_map_ = program.GetProcNodeMapping();
    std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
    for (shared_ptr<ProcedureASTNode> child : children) {
        child->Extract(*this);
    }
}

void UsesExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
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
* Uses: All variables on RHS of assignment
*/
void UsesExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {
    std::string proc_name = assign.GetParentProcIndex();
    int line_no = assign.GetLineIndex();

    std::vector<Variable> rhs = assign.GetRightVars();
    for (Variable var : rhs) {
        this->AddToUses(proc_name, var);
        this->AddToUses(line_no, var);
        this->SetIndirectUses(var);
    }
}

void UsesExtractor::ExtractCallNode(const CallStatementASTNode& call) {
    Procedure parent_procedure = call.GetParentProcIndex();
    Procedure called_proc = call.GetProcedure();

    this->proc_call_stack_.push_back(parent_procedure);
    this->parent_smts_.push_back(call.GetLineIndex());

    if (IsExtractedProcedure(called_proc)) {
        // Set uses from cached sets
        std::shared_ptr<std::set<Variable>> cached_uses = this->proc_uses_.at(called_proc);
        for (Variable used_var : *cached_uses) {
            this->SetIndirectUses(used_var);
        }
    }
    else {
        std::shared_ptr<ProcedureASTNode> called_proc_node = this->proc_node_map_.at(called_proc);
        called_proc_node->Extract(*this);
    }

    this->parent_smts_.pop_back();
    this->proc_call_stack_.pop_back();
}

// Uses: variable used by print
void UsesExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {
    Variable var = print.GetVariable();
    std::string proc_name = print.GetParentProcIndex();
    int line_no = print.GetLineIndex();

    this->AddToUses(proc_name, var);
    this->AddToUses(line_no, var);
    this->SetIndirectUses(var);
}

void UsesExtractor::ExtractReadNode(const ReadStatementASTNode& read) {}

void UsesExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
    std::shared_ptr<ConditionExpression> cond = if_stmt.GetCondition();
    cond->Extract(*this);

    // Remember parent container statement, and all uses for children
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

void UsesExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
    std::shared_ptr<ConditionExpression> cond = while_stmt.GetCondition();
    cond->Extract(*this);

    this->parent_smts_.push_back(while_stmt.GetLineIndex());
    std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
    for (std::shared_ptr<StatementASTNode> child : children) {
        child->Extract(*this);
    }
    this->parent_smts_.pop_back();
}

// Uses: all variables involved in a conditional expression
void UsesExtractor::ExtractConditionExpression(const ConditionExpression& cond) {
    std::string proc_name = cond.GetParentProcIndex();
    int line_no = cond.GetLineIndex();

    std::vector<Variable> vars = cond.GetVariables();
    for (Variable var : vars) {
        this->AddToUses(line_no, var);
        this->AddToUses(proc_name, var);
        this->SetIndirectUses(var);
    }
}

bool UsesExtractor::IsExtractedProcedure(Procedure p) {
    return this->proc_uses_.find(p) != this->proc_uses_.end();
}

void UsesExtractor::InitCachedSet(Procedure p) {
    std::shared_ptr<std::set<Variable>> uses_set(new std::set<Variable>());
    this->proc_uses_.insert(std::make_pair(p, uses_set));
}

// Sets uses on the variable for parent procedure calls and container stmts
void UsesExtractor::SetIndirectUses(Variable var) {
    for (Procedure p : this->proc_call_stack_) {
        this->AddToUses(p, var);
    }
    for (StmtNum l : this->parent_smts_) {
        this->AddToUses(l, var);
    }
}

void UsesExtractor::AddToUses(StmtNum line, Variable var) {
    this->write_manager_->SetUses(line, var);
}

void UsesExtractor::AddToUses(Procedure proc, Variable var) {
    this->write_manager_->SetUses(proc, var);
    std::shared_ptr<std::set<Variable>> cached_set = this->proc_uses_.at(proc);
    cached_set->insert(var);
}

