#include "UsesModifiesExtractor.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"

#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"

#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"
#include "../ast/ConditionExpression.h"

UsesModifiesExtractor::UsesModifiesExtractor(std::shared_ptr<WritePKBManager> manager) : NodeExtractor(manager) {}

void UsesModifiesExtractor::ExtractProgramNode(const ProgramNode& program) {
    this->proc_node_map_ = program.GetProcNodeMapping();
    std::vector<shared_ptr<ProcedureASTNode>> children = program.GetChildren();
    for (shared_ptr<ProcedureASTNode> child : children) {
        child->Extract(*this);
    }
}

void UsesModifiesExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
    std::vector<std::shared_ptr<StatementASTNode>> children = proc.GetChildren();
    for (std::shared_ptr<StatementASTNode> child : children) {
        child->Extract(*this);
    }
}

/*
* Uses: All variables on RHS of assignment
* Modifies: Variable on LHS of assignment
*/
void UsesModifiesExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {
    std::string proc_name = assign.GetParentProcIndex();
    int line_no = assign.GetLineIndex();

    std::vector<Variable> rhs = assign.GetRightVars();
    for (Variable var : rhs) {
        this->AddToUses(proc_name, var);
        this->AddToUses(line_no, var);
        this->SetIndirectUses(var);
    }

    Variable lhs = assign.GetLeft();
    this->AddToModifies(proc_name, lhs);
    this->AddToModifies(line_no, lhs);
    this->SetIndirectModifies(lhs);
}

void UsesModifiesExtractor::ExtractCallNode(const CallStatementASTNode& call) {
    Procedure called_proc = call.GetProcedure();
    if (this->proc_node_map_.find(called_proc) == this->proc_node_map_.end()) {
        return;
    }

    Procedure parent_procedure = call.GetParentProcIndex();
    this->proc_call_stack_.push_back(parent_procedure);
    this->parent_smts_.push_back(call.GetLineIndex());

    std::shared_ptr<ProcedureASTNode> called_proc_node = this->proc_node_map_.at(called_proc);
    called_proc_node->Extract(*this);

    this->parent_smts_.pop_back();
    this->proc_call_stack_.pop_back();
}

// Uses: variable used by print
void UsesModifiesExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {
    Variable var = print.GetVariable();
    std::string proc_name = print.GetParentProcIndex();
    int line_no = print.GetLineIndex();

    this->AddToUses(proc_name, var);
    this->AddToUses(line_no, var);
    this->SetIndirectUses(var);
}

// Modifies: variable used by read
void UsesModifiesExtractor::ExtractReadNode(const ReadStatementASTNode& read) {
    Variable var = read.GetReadVariable();
    std::string proc_name = read.GetParentProcIndex();
    int line_no = read.GetLineIndex();

    this->AddToModifies(proc_name, var);
    this->AddToModifies(line_no, var);
    this->SetIndirectModifies(var);
}

void UsesModifiesExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
    std::shared_ptr<ConditionExpression> cond = if_stmt.GetCondition();
    cond->Extract(*this);

    // Remember parent container statement, and all UsesModifies for children
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

void UsesModifiesExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
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
void UsesModifiesExtractor::ExtractConditionExpression(const ConditionExpression& cond) {
    std::string proc_name = cond.GetParentProcIndex();
    int line_no = cond.GetLineIndex();

    std::vector<Variable> vars = cond.GetVariables();
    for (Variable var : vars) {
        this->AddToUses(line_no, var);
        this->AddToUses(proc_name, var);
        this->SetIndirectUses(var);
    }
}

void UsesModifiesExtractor::AddToUses(StmtNum line, Variable var) {
    std::pair<StmtNum, Variable> uses = std::make_pair(line, var);
    if (this->stmt_uses_cache_.find(uses) == this->stmt_uses_cache_.end()) {
        this->write_manager_->SetUses(line, var);
        this->stmt_uses_cache_.insert(uses);
    }
}

void UsesModifiesExtractor::AddToUses(Procedure proc, Variable var) {
    std::pair<Procedure, Variable> uses = std::make_pair(proc, var);
    if (this->procedure_uses_cache_.find(uses) == this->procedure_uses_cache_.end()) {
        this->write_manager_->SetUses(proc, var);
        this->procedure_uses_cache_.insert(uses);
    }
}

void UsesModifiesExtractor::AddToModifies(StmtNum line, Variable var) {
    std::pair<StmtNum, Variable> modifies = std::make_pair(line, var);
    if (this->stmt_modifies_cache_.find(modifies) == this->stmt_modifies_cache_.end()) {
        this->write_manager_->SetModifies(line, var);
        this->stmt_modifies_cache_.insert(modifies);
    }
}

void UsesModifiesExtractor::AddToModifies(Procedure proc, Variable var) {
    std::pair<Procedure, Variable> modifies = std::make_pair(proc, var);
    if (this->procedure_modifies_cache_.find(modifies) == this->procedure_modifies_cache_.end()) {
        this->write_manager_->SetModifies(proc, var);
        this->procedure_modifies_cache_.insert(modifies);
    }
}

// Sets uses on the variable for parent procedure calls and container stmts
void UsesModifiesExtractor::SetIndirectUses(Variable var) {
    for (Procedure p : this->proc_call_stack_) {
        this->AddToUses(p, var);
    }
    for (StmtNum l : this->parent_smts_) {
        this->AddToUses(l, var);
    }
}

// Sets modifies on the variable for parent procedure calls and container stmts
void UsesModifiesExtractor::SetIndirectModifies(Variable var) {
    for (Procedure p : this->proc_call_stack_) {
        this->AddToModifies(p, var);
    }
    for (StmtNum l : this->parent_smts_) {
        this->AddToModifies(l, var);
    }
}
