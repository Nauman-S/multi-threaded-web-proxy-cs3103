#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "../Utils/Token.h"
#include "../Utils/type/TypeDef.h"

#include "./tokenizer/SourceToken.h"
#include "./ast/ASTNode.h"
#include "./ast/ProgramNode.h"
#include "./ast/ProcedureASTNode.h"
#include "./ast/CallStatementASTNode.h"
#include "./ast/ReadStatementASTNode.h"
#include "./ast/PrintStatementASTNode.h"
#include "./ast/IfStatementASTNode.h"
#include "./ast/WhileStatementASTNode.h"
#include "./ast/AssignStatementASTNode.h"
#include "./ast/ConditionExpression.h"
#include "./ast/StatementASTNode.h"

#include "../Utils/type/TypeDef.h"

class SourceParser {
public:
	std::shared_ptr<ProgramNode> Parse(std::shared_ptr<std::vector<SourceToken>>);

private:
    int token_idx = 0;
    int line_idx = 1;
    void IncrementTokenIdx();
    void IncrementLineIdex();
	std::shared_ptr<ProcedureASTNode> ParseProcedure(std::shared_ptr<std::vector<SourceToken>>);
	std::shared_ptr<StatementASTNode> ParseStatement(std::shared_ptr<std::vector<SourceToken>>, Procedure&);
	std::shared_ptr<CallStatementASTNode> ParseCallStatement(std::shared_ptr<std::vector<SourceToken>>, Procedure&);
	std::shared_ptr<ReadStatementASTNode> ParseReadStatement(std::shared_ptr<std::vector<SourceToken>>, Procedure&);
	std::shared_ptr<PrintStatementASTNode> ParsePrintStatement(std::shared_ptr<std::vector<SourceToken>>, Procedure&);
	std::shared_ptr<IfStatementASTNode> ParseIfStatement(std::shared_ptr<std::vector<SourceToken>>, Procedure&);
	std::shared_ptr<WhileStatementASTNode> ParseWhileStatement(std::shared_ptr<std::vector<SourceToken>>, Procedure&);
	std::shared_ptr<AssignStatementASTNode> ParseAssignStatement(std::shared_ptr<std::vector<SourceToken>>, Procedure&);
	std::shared_ptr<ConditionExpression> ParseConditionExpression(std::shared_ptr<std::vector<SourceToken>>, Procedure&);

	std::string JoinWithDelimiter(std::vector<std::string>&, std::string);
};