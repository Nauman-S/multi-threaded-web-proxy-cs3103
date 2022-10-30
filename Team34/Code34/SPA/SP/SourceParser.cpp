#include "SourceParser.h"

#include <vector>
#include <iostream>

#include "./ast/IfStatementASTNode.h"
#include "../Utils/type/TypeDef.h"

using namespace std;

std::shared_ptr<ProgramNode> SourceParser::Parse() {
    std::shared_ptr<ProgramNode> programNode(new ProgramNode());
    while (token_idx < static_cast<int>(tokens->size())) {
        shared_ptr<ProcedureASTNode> p_node = ParseProcedure();
        programNode->AddProcedure(p_node);
    }
    return programNode;
}

std::shared_ptr<ProcedureASTNode> SourceParser::ParseProcedure() {
    // Procedure name {
    std::shared_ptr<ProcedureASTNode> procedure(new ProcedureASTNode());
    vector<std::shared_ptr<StatementASTNode>> children = {};
    Procedure p;
    if (tokens->at(token_idx).IsProcedure()) {
        IncrementTokenIdx();
    }
    p = tokens->at(token_idx++).GetStringVal();
    if (tokens->at(token_idx).GetType() == SourceTokenType::kLeftCurly) {
        IncrementTokenIdx();
    }
    while (tokens->at(token_idx).GetType() != SourceTokenType::kRightCurly) {
        std::shared_ptr<StatementASTNode> s_node = ParseStatement(p);
        children.push_back(s_node);
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kRightCurly) {
        IncrementTokenIdx();
    }
    procedure->SetChildren(children);
    procedure->SetProc(p);

    return procedure;
}

shared_ptr<StatementASTNode> SourceParser::ParseStatement(Procedure& proc) {
    std::shared_ptr<StatementASTNode> s_node;
    if (tokens->at(token_idx).GetType() == SourceTokenType::kName && tokens->at(token_idx + 1).GetType() == SourceTokenType::kEqual) {
        // Variable followed by equal sign to be parsed as assign
        s_node = ParseAssignStatement(proc);
    } else if (tokens->at(token_idx).IsIf()) {
        // cout << "if" << line_idx << endl;
        s_node = ParseIfStatement(proc);
    } else if (tokens->at(token_idx).IsWhile()) {
        // cout << "while" << line_idx << endl;
        s_node = ParseWhileStatement(proc);
    } else if (tokens->at(token_idx).IsRead()) {
        // cout << "read" << line_idx << endl;
        s_node = ParseReadStatement(proc);
    } else if (tokens->at(token_idx).IsPrint()) {
        // cout << "print" << line_idx << endl;
        s_node = ParsePrintStatement(proc);
    } else if (tokens->at(token_idx).IsCall()) {
        s_node = ParseCallStatement(proc);
    } else {
    }
    s_node->SetParentProcIndex(proc);
    return s_node;
}

shared_ptr<IfStatementASTNode> SourceParser::ParseIfStatement(Procedure& proc) {
    // if (...) then {...} else {...}
    shared_ptr<IfStatementASTNode> if_node(new IfStatementASTNode());
    StmtNum line_index = line_idx;
    if_node->SetLineIndex(line_index);
    if (tokens->at(token_idx).IsIf()) {
        IncrementTokenIdx();
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kLeftRound) {
        IncrementTokenIdx();
    }
    shared_ptr<ConditionExpression> cond = ParseConditionExpression(proc);
    cond->SetParentProcIndex(proc);
    if (tokens->at(token_idx).IsThen()) {
        IncrementTokenIdx();
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kLeftCurly) {
        IncrementTokenIdx();
    }
    vector<std::shared_ptr<StatementASTNode>> if_children = {};
    while (tokens->at(token_idx).GetType() != SourceTokenType::kRightCurly) {
        std::shared_ptr<StatementASTNode> s_node = ParseStatement(proc);
        s_node->SetParentSatementLineIndex(line_index);
        if_children.push_back(s_node);
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kRightCurly) {
        IncrementTokenIdx();
    }
    if (tokens->at(token_idx).IsElse()) {
        IncrementTokenIdx();
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kLeftCurly) {
        IncrementTokenIdx();
    }
    vector<std::shared_ptr<StatementASTNode>> else_children = {};
    while (tokens->at(token_idx).GetType() != SourceTokenType::kRightCurly) {
        std::shared_ptr<StatementASTNode> s_node = ParseStatement(proc);
        s_node->SetParentSatementLineIndex(line_index);
        else_children.push_back(s_node);
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kRightCurly) {
        IncrementTokenIdx();
    }
    if_node->SetConditionExpression(cond);
    if_node->SetIfChildren(if_children);
    if_node->SetElseChildren(else_children);
    return if_node;
}

shared_ptr<ConditionExpression> SourceParser::ParseConditionExpression(Procedure& proc) {
    shared_ptr<ConditionExpression> cond(new ConditionExpression());
    StmtNum line_index = line_idx;
    vector<Variable> vars = {};
    vector<Constant> cons = {};
    cond->SetLineIndex(line_index);
    IncrementLineIdex();
    int round_count = 1;
    while (!(tokens->at(token_idx).GetType() == SourceTokenType::kRightRound && round_count == 1)) {
        if (tokens->at(token_idx).GetType() == SourceTokenType::kName) {
            Variable v = tokens->at(token_idx).GetStringVal();
            vars.push_back(v);
        } else if (tokens->at(token_idx).GetType() == SourceTokenType::kInteger) {
            Constant c = stoi(tokens->at(token_idx).GetStringVal());
            cons.push_back(c);
        } else if (tokens->at(token_idx).GetType() == SourceTokenType::kLeftRound) {
            round_count += 1;
        } else if (tokens->at(token_idx).GetType() == SourceTokenType::kRightRound) {
            round_count -= 1;
        } else {

        }
        IncrementTokenIdx();
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kRightRound) {
        IncrementTokenIdx();
    }
    cond->SetVariables(vars);
    cond->SetConstants(cons);

    return cond;
}

shared_ptr<AssignStatementASTNode> SourceParser::ParseAssignStatement(Procedure& proc) {
    // a = ...;
    shared_ptr<AssignStatementASTNode> a_node(new AssignStatementASTNode());
    Variable l_var;
    StmtNum line_index = line_idx;
    a_node->SetLineIndex(line_index);
    IncrementLineIdex();
    l_var = tokens->at(token_idx).GetStringVal();
    IncrementTokenIdx();
    if (tokens->at(token_idx).GetType() == SourceTokenType::kEqual) {
        IncrementTokenIdx();
    }
    a_node->SetLeft(l_var);
    std::vector<std::string> infix_tokens;
    vector<Variable> r_vars = {};
    vector<Constant> r_cons = {};
    while (tokens->at(token_idx).GetType() != SourceTokenType::kSemiColon) {
        infix_tokens.push_back(tokens->at(token_idx).GetStringVal());
        if (tokens->at(token_idx).GetType() == SourceTokenType::kName) {
            Variable r_var = tokens->at(token_idx).GetStringVal();
            r_vars.push_back(r_var);
        } else if (tokens->at(token_idx).GetType() == SourceTokenType::kInteger) {
            Constant r_con = stoi(tokens->at(token_idx).GetStringVal());
            r_cons.push_back(r_con);
        }
        IncrementTokenIdx();
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kSemiColon) {
        IncrementTokenIdx();
    }
    a_node->SetRightVars(r_vars);
    a_node->SetRightCons(r_cons);
    std::string infix = this->JoinWithDelimiter(infix_tokens, " ");
    a_node->SetInfix(infix);
    return a_node;
}

shared_ptr<WhileStatementASTNode> SourceParser::ParseWhileStatement(Procedure& proc) {
    shared_ptr<WhileStatementASTNode> w_node(new WhileStatementASTNode());
    vector<shared_ptr<StatementASTNode>> children = {};
    StmtNum line_index = line_idx;
    w_node->SetLineIndex(line_index);
    if (tokens->at(token_idx).GetStringVal() == "while") {
        IncrementTokenIdx();
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kLeftRound) {
        IncrementTokenIdx();
    }
    shared_ptr<ConditionExpression> cond = ParseConditionExpression(proc);
    cond->SetParentProcIndex(proc);
    if (tokens->at(token_idx).GetType() == SourceTokenType::kLeftCurly) {
        IncrementTokenIdx();
    }
    while (tokens->at(token_idx).GetType() != SourceTokenType::kRightCurly) {
        shared_ptr<StatementASTNode> s_node = ParseStatement(proc);
        s_node->SetParentSatementLineIndex(line_index);
        children.push_back(s_node);
    }
    if (tokens->at(token_idx).GetType() == SourceTokenType::kRightCurly) {
        IncrementTokenIdx();
    }
    w_node->SetChildren(children);
    w_node->SetConditionExpression(cond);
    return w_node;
}

shared_ptr<ReadStatementASTNode> SourceParser::ParseReadStatement(Procedure& proc) {
    shared_ptr<ReadStatementASTNode> r_node(new ReadStatementASTNode());
    StmtNum line_index = line_idx;
    r_node->SetLineIndex(line_index);
    IncrementLineIdex();
    if (tokens->at(token_idx).IsRead()) {
        IncrementTokenIdx();
    }
    Variable var_index = tokens->at(token_idx).GetStringVal();
    r_node->SetVariable(var_index);
    IncrementTokenIdx();
    if (tokens->at(token_idx).GetType() == SourceTokenType::kSemiColon) {
        IncrementTokenIdx();
    }
    return r_node;
}

shared_ptr<PrintStatementASTNode> SourceParser::ParsePrintStatement(Procedure& proc) {
    shared_ptr<PrintStatementASTNode> p_node(new PrintStatementASTNode());
    StmtNum line_index = line_idx;
    p_node->SetLineIndex(line_index);
    IncrementLineIdex();
    if (tokens->at(token_idx).IsPrint()) {
        IncrementTokenIdx();
    }
    Variable var_index = tokens->at(token_idx).GetStringVal();
    p_node->SetVariable(var_index);
    IncrementTokenIdx();
    if (tokens->at(token_idx).GetType() == SourceTokenType::kSemiColon) {
        IncrementTokenIdx();
    }
    return p_node;
}

shared_ptr<CallStatementASTNode> SourceParser::ParseCallStatement(Procedure& proc) {
    shared_ptr<CallStatementASTNode> p_node(new CallStatementASTNode());
    StmtNum line_index = line_idx;
    p_node->SetLineIndex(line_index);
    IncrementLineIdex();
    if (tokens->at(token_idx).IsCall()) {
        IncrementTokenIdx();
    }
    Procedure proc_index = tokens->at(token_idx).GetStringVal();
    p_node->SetProcedure(proc_index);
    IncrementTokenIdx();
    if (tokens->at(token_idx).GetType() == SourceTokenType::kSemiColon) {
        IncrementTokenIdx();
    }
    return p_node;
}

std::string SourceParser::JoinWithDelimiter(std::vector<std::string>& values, std::string delimiter) {
    std::string result = "";
    for (unsigned int i = 0; i < values.size(); i++) {
        result += values[i];
        if (i != values.size() - 1) {
            result += delimiter; // Add delimiter only if not last element in vector
        }
    }
    return result;
}

void SourceParser::IncrementLineIdex() { line_idx += 1; }

void SourceParser::IncrementTokenIdx() { token_idx += 1; }

void SourceParser::SetTokens(shared_ptr<vector<SourceToken>> source_tokens) {
    tokens = source_tokens;
}