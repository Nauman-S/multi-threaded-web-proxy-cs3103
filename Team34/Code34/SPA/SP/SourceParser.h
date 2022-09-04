#pragma once
# include <list>
# include "../Utils/Token.h"
#include "SourceToken.h"
# include "ASTNode.h"
# include "ProgramNode.h"
# include "ProcedureASTNode.h"
# include "CallStatementASTNode.h"
# include "ReadStatementASTNode.h"
# include "PrintStatementASTNode.h"
# include "IfStatementASTNode.h"
# include "WhileStatementASTNode.h"
# include "AssignStatementASTNode.h"
# include "ConditionExpression.h"
# include "LineIndex.h"
# include "StatementASTNode.h"
# include "VariableIndex.h"
# include "ProcedureIndex.h"
# include <map>
# include <string>
# include <vector>

class SourceParser {
public:
	ProgramNode parse(std::string& source_filename);

	ProcedureASTNode parseProcedure(std::vector<SourceToken>, int& token_idx, int& line_idx);

	StatementASTNode parseStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	CallStatementASTNode parseCallStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	ReadStatementASTNode parseReadStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	PrintStatementASTNode parsePrintStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	IfStatementASTNode parseIfStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	WhileStatementASTNode parseWhileStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	AssignStatementASTNode parseAssignStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	ConditionExpression parseConditionExpression(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::map<StatementASTNode, LineIndex> si_mapping;
	std::map<LineIndex, StatementASTNode> is_mapping;
};