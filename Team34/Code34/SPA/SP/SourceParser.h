#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "../Utils/Token.h"
#include "SourceToken.h"
#include "ASTNode.h"
#include "ProgramNode.h"
#include "ProcedureASTNode.h"
#include "CallStatementASTNode.h"
#include "ReadStatementASTNode.h"
#include "PrintStatementASTNode.h"
#include "IfStatementASTNode.h"
#include "WhileStatementASTNode.h"
#include "AssignStatementASTNode.h"
#include "ConditionExpression.h"
#include "LineIndex.h"
#include "StatementASTNode.h"
#include "VariableIndex.h"
#include "ProcedureIndex.h"

class SourceParser {
public:
	ProgramNode parse(std::string& source_filename);

	ProcedureASTNode parseProcedure(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<StatementASTNode> parseStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<CallStatementASTNode> parseCallStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<ReadStatementASTNode> parseReadStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<PrintStatementASTNode> parsePrintStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<IfStatementASTNode> parseIfStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<WhileStatementASTNode> parseWhileStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<AssignStatementASTNode> parseAssignStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<ConditionExpression> parseConditionExpression(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::map<std::shared_ptr<StatementASTNode>, LineIndex> si_mapping;
	std::map<LineIndex, std::shared_ptr<StatementASTNode>> is_mapping;
};