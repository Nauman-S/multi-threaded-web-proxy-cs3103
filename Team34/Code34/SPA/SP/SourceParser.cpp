#include "SourceParser.h"

#include <vector>
#include <iostream>

#include "./tokenizer/SourceLexer.h"
#include "./ast/IfStatementASTNode.h"
#include "../Utils/type/TypeDef.h"

using namespace std;

std::shared_ptr<ProgramNode> SourceParser::Parse(std::string& source_filename) {
	SourceLexer lexer = SourceLexer(source_filename);
	vector<SourceToken> tokens = lexer.GetAllTokens();
	std::shared_ptr<ProgramNode> programNode (new ProgramNode());
	int token_idx = 0;
	int line_idx = 1;
	vector<shared_ptr<ProcedureASTNode>> children = {};
	while (token_idx < (int) tokens.size()) {
		shared_ptr<ProcedureASTNode> p_node = ParseProcedure(tokens, token_idx, line_idx);
		children.push_back(p_node);
	}
	programNode->SetChildren(children);
	return programNode;
}

std::shared_ptr<ProcedureASTNode> SourceParser::ParseProcedure(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
	// Procedure name {
	std::shared_ptr<ProcedureASTNode> procedure (new ProcedureASTNode());
	vector<std::shared_ptr<StatementASTNode>> children = {};
	Procedure p;
	token_idx += 1;
	p = tokens.at(token_idx).GetStringVal();
	token_idx += 2;
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		std::shared_ptr<StatementASTNode> s_node = ParseStatement(tokens, token_idx, line_idx, p);
		children.push_back(s_node);
	}
	token_idx += 1;
	procedure->SetChildren(children);
	procedure->SetProc(p);

	this->proc_name_to_node_.insert(std::make_pair(p, procedure));
	return procedure;
}

shared_ptr<StatementASTNode> SourceParser::ParseStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, Procedure& proc) {
	std::shared_ptr<StatementASTNode> s_node;
	if (tokens.at(token_idx).GetType() == SourceTokenType::kName && tokens.at(token_idx + 1).GetType() == SourceTokenType::kEqual) {
		// Variable followed by equal sign to be parsed as assign
		s_node = ParseAssignStatement(tokens, token_idx, line_idx, proc);
	}
	else if (tokens.at(token_idx).IsIf()) {
		// cout << "if" << line_idx << endl;
		s_node = ParseIfStatement(tokens, token_idx, line_idx, proc);
	}
	else if (tokens.at(token_idx).IsWhile()) {
		// cout << "while" << line_idx << endl;
		s_node = ParseWhileStatement(tokens, token_idx, line_idx, proc);
	}
	else if (tokens.at(token_idx).IsRead()) {
		// cout << "read" << line_idx << endl;
		s_node = ParseReadStatement(tokens, token_idx, line_idx, proc);
	} else if (tokens.at(token_idx).IsPrint()) {
		// cout << "print" << line_idx << endl;
		s_node = ParsePrintStatement(tokens, token_idx, line_idx, proc);
	}
	else if (tokens.at(token_idx).IsCall()) {
		s_node = ParseCallStatement(tokens, token_idx, line_idx, proc);
	} else {
	}
	s_node->SetParentProcIndex(proc);
	return s_node;
}

shared_ptr<IfStatementASTNode> SourceParser::ParseIfStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, Procedure& proc) {
	// if (...) then {...} else {...}
	shared_ptr<IfStatementASTNode> if_node (new IfStatementASTNode());
	StmtNum line_index = line_idx;
	if_node->SetLineIndex(line_index);
	token_idx += 2;
	shared_ptr<ConditionExpression> cond = ParseConditionExpression(tokens, token_idx, line_idx, proc);
	cond->SetParentProcIndex(proc);
	token_idx += 1;
	vector<std::shared_ptr<StatementASTNode>> if_children = {};
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		std::shared_ptr<StatementASTNode> s_node = ParseStatement(tokens, token_idx, line_idx, proc);
		s_node->SetParentSatementLineIndex(line_index);
		if_children.push_back(s_node);
	}
	token_idx += 3;
	vector<std::shared_ptr<StatementASTNode>> else_children = {};
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		std::shared_ptr<StatementASTNode> s_node = ParseStatement(tokens, token_idx, line_idx, proc);
		s_node->SetParentSatementLineIndex(line_index);
		else_children.push_back(s_node);
	}
	token_idx += 1;
	if_node->SetConditionExpression(cond);
	if_node->SetIfChildren(if_children);
	if_node->SetElseChildren(else_children);
	return if_node;
}

shared_ptr<ConditionExpression> SourceParser::ParseConditionExpression(vector<SourceToken> tokens, int& token_idx, int& line_idx, Procedure& proc) {
	// (...)
	shared_ptr<ConditionExpression> cond (new ConditionExpression());
	StmtNum line_index = line_idx;
	vector<Variable> vars = {};
	vector<Constant> cons = {};
	cond->SetLineIndex(line_index);
	line_idx += 1;
	int round_count = 1;
	while (!(tokens.at(token_idx).GetType() == SourceTokenType::kRightRound && round_count == 1)) {	
		if (tokens.at(token_idx).GetType() == SourceTokenType::kName) {
			Variable v = tokens.at(token_idx).GetStringVal();
			vars.push_back(v);
		}
		else if (tokens.at(token_idx).GetType() == SourceTokenType::kInteger) {
			Constant c = stoi(tokens.at(token_idx).GetStringVal());
			cons.push_back(c);
		}
		else if (tokens.at(token_idx).GetType() == SourceTokenType::kLeftRound) {
			round_count += 1;
		}
		else if (tokens.at(token_idx).GetType() == SourceTokenType::kRightRound) {
			round_count -= 1;
		}
		else {

		}
		token_idx += 1;
	}
	cond->SetVariables(vars);
	cond->SetConstants(cons);
	token_idx += 2;   // ) { x || ) then {
	return cond;
}

shared_ptr<AssignStatementASTNode> SourceParser::ParseAssignStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, Procedure& proc) {
	// a = ...;
	shared_ptr<AssignStatementASTNode> a_node(new AssignStatementASTNode());
	Variable l_var;
	StmtNum line_index = line_idx;
	a_node->SetLineIndex(line_index);
	line_idx += 1;
	l_var = tokens.at(token_idx).GetStringVal();
	token_idx += 2;
	a_node->SetLeft(l_var);
	std::vector<std::string> infix_tokens;
	vector<Variable> r_vars = {};
	vector<Constant> r_cons = {};
	while (tokens.at(token_idx).GetType() != SourceTokenType::kSemiColon) {
		infix_tokens.push_back(tokens.at(token_idx).GetStringVal());
		if (tokens.at(token_idx).GetType() == SourceTokenType::kName) {
			Variable r_var = tokens.at(token_idx).GetStringVal();
			r_vars.push_back(r_var);
		}
		else if (tokens.at(token_idx).GetType() == SourceTokenType::kInteger) {
			Constant r_con = stoi(tokens.at(token_idx).GetStringVal());
			r_cons.push_back(r_con);
		}
		token_idx += 1;
	}
	token_idx += 1;
	a_node->SetRightVars(r_vars);
	a_node->SetRightCons(r_cons);
	std::string infix = this->JoinWithDelimiter(infix_tokens, " ");
	a_node->SetInfix(infix);
	return a_node;
}

shared_ptr<WhileStatementASTNode> SourceParser::ParseWhileStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, Procedure& proc) {
	// while ()
	shared_ptr<WhileStatementASTNode> w_node (new WhileStatementASTNode());
	vector<shared_ptr<StatementASTNode>> children = {};
	StmtNum line_index = line_idx;
	w_node->SetLineIndex(line_index);
	token_idx += 2;
	shared_ptr<ConditionExpression> cond = ParseConditionExpression(tokens, token_idx, line_idx, proc);
	cond->SetParentProcIndex(proc);
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		shared_ptr<StatementASTNode> s_node = ParseStatement(tokens, token_idx, line_idx, proc);
		s_node->SetParentSatementLineIndex(line_index);
		children.push_back(s_node);
	}
	token_idx += 1;
	w_node->SetChildren(children);
	w_node->SetConditionExpression(cond);
	return w_node;
}

shared_ptr<ReadStatementASTNode> SourceParser::ParseReadStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, Procedure& proc) {
	// read x
	shared_ptr<ReadStatementASTNode> r_node (new ReadStatementASTNode());
	StmtNum line_index = line_idx;
	r_node->SetLineIndex(line_index);
	line_idx += 1;
	token_idx += 1;
	Variable var_index = tokens.at(token_idx).GetStringVal();
	r_node->SetVariable(var_index);
	token_idx += 2;
	return r_node;
}

shared_ptr<PrintStatementASTNode> SourceParser::ParsePrintStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, Procedure& proc) {
	// read x
	shared_ptr<PrintStatementASTNode> p_node (new PrintStatementASTNode());
	StmtNum line_index = line_idx;
	p_node->SetLineIndex(line_index);
	line_idx += 1;
	token_idx += 1;
	Variable var_index = tokens.at(token_idx).GetStringVal();
	p_node->SetVariable(var_index);
	token_idx += 2;
	return p_node;
}

shared_ptr<CallStatementASTNode> SourceParser::ParseCallStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, Procedure& proc) {
	// call p
	shared_ptr<CallStatementASTNode> p_node(new CallStatementASTNode());
	StmtNum line_index = line_idx;
	p_node->SetLineIndex(line_index);
	line_idx += 1;
	token_idx += 1;
	Procedure proc_index = tokens.at(token_idx).GetStringVal();
	p_node->SetProcedure(proc_index);
	token_idx += 2;
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