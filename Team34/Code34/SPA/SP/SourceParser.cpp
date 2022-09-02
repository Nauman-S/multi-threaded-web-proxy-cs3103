#include "SourceParser.h"
#include "SourceLexer.h"
#include <vector>
# include <iostream>
#include "IfStatementASTNode.h"

using namespace std;

ProgramNode SourceParser::parse(std::string& source_filename) {
	SourceLexer lexer = SourceLexer(source_filename);
	vector<SourceToken> tokens = lexer.GetAllTokens();
	ProgramNode programNode = ProgramNode();
	int token_idx = 0;
	int line_idx = 1;
	vector<ProcedureASTNode> children = {};
	while (token_idx < tokens.size()) {
		ProcedureASTNode p_node = parseProcedure(tokens, token_idx, line_idx);
		children.push_back(p_node);
	}
	programNode.setChildren(children);
	return programNode;
}

ProcedureASTNode SourceParser::parseProcedure(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
// Procedure name {
	ProcedureASTNode procedure = ProcedureASTNode();
	vector<StatementASTNode> children = {};
	token_idx += 1;
	procedure.setName(tokens.at(token_idx).GetStringVal());
	token_idx += 2;
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		StatementASTNode s_node = parseStatement(tokens, token_idx, line_idx);
		children.push_back(s_node);
	}
	token_idx += 1;
	procedure.setChildren(children);
	return procedure;
}

StatementASTNode SourceParser::parseStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
	StatementASTNode s_node;
	if (tokens.at(token_idx).GetType() == SourceTokenType::kIf) {
		s_node = parseIfStatement(tokens, token_idx, line_idx);
		s_node.setStatementType(StatementType::sif, "sif");
		
	}
	else if (tokens.at(token_idx).GetType() == SourceTokenType::kWhile) {
		s_node = parseWhileStatement(tokens, token_idx, line_idx);
		s_node.setStatementType(StatementType::swhile, "swhile");
	}
	else if (tokens.at(token_idx).GetType() == SourceTokenType::kRead) {
		s_node = parseReadStatement(tokens, token_idx, line_idx);
		s_node.setStatementType(StatementType::sread, "sread");
	} else if (tokens.at(token_idx).GetType() == SourceTokenType::kPrint) {
		s_node = parseReadStatement(tokens, token_idx, line_idx);
		s_node.setStatementType(StatementType::sprint, "sprint");
	} else {
		s_node = parseAssignStatement(tokens, token_idx, line_idx);
		s_node.setStatementType(StatementType::sassign, "sassign");
	}
	return s_node;
}

IfStatementASTNode SourceParser::parseIfStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
	// if (...) then {...} else {...}
	IfStatementASTNode if_node = IfStatementASTNode();
	LineIndex line_index = LineIndex();
	line_index.setLineNum(line_idx);
	if_node.setLineIndex(line_index);
	token_idx += 2;
	ConditionExpression cond = parseConditionExpression(tokens, token_idx, line_idx);
	token_idx += 2;
	vector<StatementASTNode> if_children = {};
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		StatementASTNode s_node = parseStatement(tokens, token_idx, line_idx);
		if_children.push_back(s_node);
	}
	token_idx += 3;
	vector<StatementASTNode> else_children = {};
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		StatementASTNode s_node = parseStatement(tokens, token_idx, line_idx);
		else_children.push_back(s_node);
	}
	token_idx += 1;
	if_node.setConditionExpression(cond);
	if_node.setIfChildren(if_children);
	if_node.setElseChildren(else_children);
	return if_node;
}

ConditionExpression SourceParser::parseConditionExpression(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
	// (...)
	ConditionExpression cond = ConditionExpression();
	cond.setStatementType(StatementType::sexpre, "sexpre");
	LineIndex line_index = LineIndex();
	line_index.setLineNum(line_idx);
	cond.setLineIndex(line_index);
	line_idx += 1;
	string val = "";
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightRound) {
		val += tokens.at(token_idx).GetStringVal();
		token_idx += 1;
	}
	cond.setValue(val);
	token_idx += 1;
	return cond;
}

AssignStatementASTNode SourceParser::parseAssignStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
	// a = ...;
	AssignStatementASTNode a_node = AssignStatementASTNode();
	VariableIndex l_var = VariableIndex();
	LineIndex line_index = LineIndex();
	line_index.setLineNum(line_idx);
	a_node.setLineIndex(line_index);
	line_idx += 1;
	l_var.setName(tokens.at(token_idx).GetStringVal());
	token_idx += 2;
	a_node.setLeft(l_var);
	vector<VariableIndex> r_vars = {};
	while (tokens.at(token_idx).GetType() != SourceTokenType::kSemiColon) {
		if (tokens.at(token_idx).GetType() == SourceTokenType::kName) {
			VariableIndex r_var = VariableIndex();
			r_var.setName(tokens.at(token_idx).GetStringVal());
			r_vars.push_back(r_var);
		}
		token_idx += 1;
	}
	token_idx += 1;
	a_node.setRight(r_vars);
	return a_node;
}

WhileStatementASTNode SourceParser::parseWhileStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
	// while ()
	WhileStatementASTNode w_node = WhileStatementASTNode();
	vector<StatementASTNode> children = {};
	LineIndex line_index = LineIndex();
	line_index.setLineNum(line_idx);
	w_node.setLineIndex(line_index);
	line_idx += 1;
	token_idx += 2;
	ConditionExpression cond = parseConditionExpression(tokens, token_idx, line_idx);
	while (tokens.at(token_idx).GetType() != SourceTokenType::kRightCurly) {
		StatementASTNode s_node = parseStatement(tokens, token_idx, line_idx);
		children.push_back(s_node);
	}
	w_node.setChildren(children);
	w_node.setConditionExpression(cond);
	return w_node;
}

ReadStatementASTNode SourceParser::parseReadStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
	// read x
	ReadStatementASTNode r_node = ReadStatementASTNode();
	LineIndex line_index = LineIndex();
	line_index.setLineNum(line_idx);
	r_node.setLineIndex(line_index);
	line_idx += 1;
	token_idx += 1;
	VariableIndex var_index = VariableIndex();
	var_index.setName(tokens.at(token_idx).GetStringVal());
	r_node.setVariable(var_index);
	token_idx += 2;
	return r_node;
}

PrintStatementASTNode SourceParser::parsePrintStatement(vector<SourceToken> tokens, int& token_idx, int& line_idx) {
	// read x
	PrintStatementASTNode p_node = PrintStatementASTNode();
	LineIndex line_index = LineIndex();
	line_index.setLineNum(line_idx);
	p_node.setLineIndex(line_index);
	line_idx += 1;
	token_idx += 1;
	VariableIndex var_index = VariableIndex();
	var_index.setName(tokens.at(token_idx).GetStringVal());
	p_node.setVariable(var_index);
	token_idx += 2;
	return p_node;
}