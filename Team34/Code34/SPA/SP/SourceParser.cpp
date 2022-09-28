#include "SourceParser.h"

#include <vector>
#include <iostream>

#include "./tokenizer/SourceLexer.h"
#include "./ast/IfStatementASTNode.h"

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
	ProcedureIndex p = ProcedureIndex();
	token_idx += 1;
	p.SetName(tokens.at(token_idx).GetStringVal());
	token_idx += 2;
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		std::shared_ptr<StatementASTNode> s_node = ParseStatement(tokens, token_idx, line_idx, p);
		children.push_back(s_node);
	}
	token_idx += 1;
	procedure->SetChildren(children);
	procedure->SetProc(p);

	this->proc_name_to_node_.insert(std::make_pair(p.GetName(), procedure));
	return procedure;
}

shared_ptr<StatementASTNode> SourceParser::ParseStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, ProcedureIndex& proc) {
	
	std::shared_ptr<StatementASTNode> s_node;
	if (tokens.at(token_idx).GetType() == SourceTokenType::kName && tokens.at(token_idx + 1).GetType() == SourceTokenType::kEqual) {
		// Variable followed by equal sign to be parsed as assign
		s_node = ParseAssignStatement(tokens, token_idx, line_idx, proc);
		s_node->SetStatementType(StatementType::sassign, "sassign");
	}
	else if (tokens.at(token_idx).IsIf()) {
		// cout << "if" << line_idx << endl;
		s_node = ParseIfStatement(tokens, token_idx, line_idx, proc);
		s_node->SetStatementType(StatementType::sif, "sif");
	}
	else if (tokens.at(token_idx).IsWhile()) {
		// cout << "while" << line_idx << endl;
		s_node = ParseWhileStatement(tokens, token_idx, line_idx, proc);
		s_node->SetStatementType(StatementType::swhile, "swhile");
	}
	else if (tokens.at(token_idx).IsRead()) {
		// cout << "read" << line_idx << endl;
		s_node = ParseReadStatement(tokens, token_idx, line_idx, proc);
		s_node->SetStatementType(StatementType::sread, "sread");
	} else if (tokens.at(token_idx).IsPrint()) {
		// cout << "print" << line_idx << endl;
		s_node = ParsePrintStatement(tokens, token_idx, line_idx, proc);
		s_node->SetStatementType(StatementType::sprint, "sprint");
	}
	else if (tokens.at(token_idx).IsCall()) {
		s_node = ParseCallStatement(tokens, token_idx, line_idx, proc);
		s_node->SetStatementType(StatementType::scall, "scall");
	} else {
	}
	s_node->SetParentProcIndex(proc);
	is_mapping.insert(pair<LineIndex, std::shared_ptr<StatementASTNode>>(s_node->GetLineIndex(), s_node));
    si_mapping.insert(pair<std::shared_ptr<StatementASTNode>, LineIndex>(s_node, s_node->GetLineIndex()));
	return s_node;
}

shared_ptr<IfStatementASTNode> SourceParser::ParseIfStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, ProcedureIndex& proc) {
	// if (...) then {...} else {...}
	shared_ptr<IfStatementASTNode> if_node (new IfStatementASTNode());
	LineIndex line_index = LineIndex();
	line_index.SetLineNum(line_idx);
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
	if_node->SetStatementType(StatementType::sif, "sif");
	return if_node;
}

shared_ptr<ConditionExpression> SourceParser::ParseConditionExpression(vector<SourceToken> tokens, int& token_idx, int& line_idx, ProcedureIndex& proc) {
	// (...)
	shared_ptr<ConditionExpression> cond (new ConditionExpression());
	cond->SetStatementType(StatementType::sexpre, "sexpre");
	LineIndex line_index = LineIndex();
	vector<VariableIndex> vars = {};
	line_index.SetLineNum(line_idx);
	cond->SetLineIndex(line_index);
	line_idx += 1;
	int round_count = 1;
	while (!(tokens.at(token_idx).GetType() == SourceTokenType::kRightRound && round_count == 1)) {	
		if (tokens.at(token_idx).GetType() == SourceTokenType::kName) {
			VariableIndex v = VariableIndex();
			v.SetName(tokens.at(token_idx).GetStringVal());
			vars.push_back(v);
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
	token_idx += 2;   // ) { x || ) then {
	return cond;
}

shared_ptr<AssignStatementASTNode> SourceParser::ParseAssignStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, ProcedureIndex& proc) {
	// a = ...;
	shared_ptr<AssignStatementASTNode> a_node(new AssignStatementASTNode());
	VariableIndex l_var = VariableIndex();
	LineIndex line_index = LineIndex();
	line_index.SetLineNum(line_idx);
	a_node->SetLineIndex(line_index);
	line_idx += 1;
	l_var.SetName(tokens.at(token_idx).GetStringVal());
	token_idx += 2;
	a_node->SetLeft(l_var);
	vector<VariableIndex> r_vars = {};
	string infix = "";
	while (tokens.at(token_idx).GetType() != SourceTokenType::kSemiColon) {
		infix += tokens.at(token_idx).GetStringVal();
		if (tokens.at(token_idx).GetType() == SourceTokenType::kName) {
			VariableIndex r_var = VariableIndex();
			r_var.SetName(tokens.at(token_idx).GetStringVal());
			r_vars.push_back(r_var);
		}
		token_idx += 1;
	}
	token_idx += 1;
	a_node->SetRight(r_vars);
	a_node->SetInfix(infix);
	a_node->SetStatementType(StatementType::sassign, "sassign");
	return a_node;
}

shared_ptr<WhileStatementASTNode> SourceParser::ParseWhileStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, ProcedureIndex& proc) {
	// while ()
	shared_ptr<WhileStatementASTNode> w_node (new WhileStatementASTNode());
	vector<shared_ptr<StatementASTNode>> children = {};
	LineIndex line_index = LineIndex();
	line_index.SetLineNum(line_idx);
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
	w_node->SetStatementType(StatementType::swhile, "swhile");
	return w_node;
}

shared_ptr<ReadStatementASTNode> SourceParser::ParseReadStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, ProcedureIndex& proc) {
	// read x
	shared_ptr<ReadStatementASTNode> r_node (new ReadStatementASTNode());
	LineIndex line_index = LineIndex();
	line_index.SetLineNum(line_idx);
	r_node->SetLineIndex(line_index);
	line_idx += 1;
	token_idx += 1;
	VariableIndex var_index = VariableIndex();
	var_index.SetName(tokens.at(token_idx).GetStringVal());
	r_node->SetVariable(var_index);
	token_idx += 2;
	r_node->SetStatementType(StatementType::sread, "sread");
	return r_node;
}

shared_ptr<PrintStatementASTNode> SourceParser::ParsePrintStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, ProcedureIndex& proc) {
	// read x
	shared_ptr<PrintStatementASTNode> p_node (new PrintStatementASTNode());
	LineIndex line_index = LineIndex();
	line_index.SetLineNum(line_idx);
	p_node->SetLineIndex(line_index);
	line_idx += 1;
	token_idx += 1;
	VariableIndex var_index = VariableIndex();
	var_index.SetName(tokens.at(token_idx).GetStringVal());
	p_node->SetVariable(var_index);
	token_idx += 2;
	p_node->SetStatementType(StatementType::sprint, "sprint");
	return p_node;
}

shared_ptr<CallStatementASTNode> SourceParser::ParseCallStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx, ProcedureIndex& proc) {
	// call p
	shared_ptr<CallStatementASTNode> p_node(new CallStatementASTNode());
	LineIndex line_index = LineIndex();
	line_index.SetLineNum(line_idx);
	p_node->SetLineIndex(line_index);
	line_idx += 1;
	token_idx += 1;
	ProcedureIndex proc_index = ProcedureIndex();
	proc_index.SetName(tokens.at(token_idx).GetStringVal());
	p_node->SetProcedure(proc_index);
	token_idx += 2;
	p_node->SetStatementType(StatementType::scall, "scall");
	return p_node;
}