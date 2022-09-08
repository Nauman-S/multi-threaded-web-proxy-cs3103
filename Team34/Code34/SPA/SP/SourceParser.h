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
	std::shared_ptr<ProgramNode> Parse(std::string& source_filename);

	std::shared_ptr<ProcedureASTNode> ParseProcedure(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<StatementASTNode> ParseStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<CallStatementASTNode> ParseCallStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<ReadStatementASTNode> ParseReadStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<PrintStatementASTNode> ParsePrintStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<IfStatementASTNode> ParseIfStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<WhileStatementASTNode> ParseWhileStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<AssignStatementASTNode> ParseAssignStatement(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::shared_ptr<ConditionExpression> ParseConditionExpression(std::vector<SourceToken>, int& token_idx, int& line_idx);

	std::map<std::shared_ptr<StatementASTNode>, LineIndex> si_mapping;
	std::map<LineIndex, std::shared_ptr<StatementASTNode>> is_mapping;
};