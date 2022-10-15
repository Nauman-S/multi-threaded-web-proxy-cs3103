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

using namespace std;

class SourceParser {
public:
    shared_ptr<ProgramNode> Parse();
    void SetTokens(shared_ptr<vector<SourceToken>>);

private:
    int token_idx = 0;
    int line_idx = 1;

    shared_ptr<vector<SourceToken>> tokens;
    void IncrementTokenIdx();
    void IncrementLineIdex();

    shared_ptr<ProcedureASTNode> ParseProcedure();
    shared_ptr<StatementASTNode> ParseStatement(Procedure&);
    shared_ptr<CallStatementASTNode> ParseCallStatement(Procedure&);
    shared_ptr<ReadStatementASTNode> ParseReadStatement(Procedure&);
    shared_ptr<PrintStatementASTNode> ParsePrintStatement(Procedure&);
    shared_ptr<IfStatementASTNode> ParseIfStatement(Procedure&);
    shared_ptr<WhileStatementASTNode> ParseWhileStatement(Procedure&);
    shared_ptr<AssignStatementASTNode> ParseAssignStatement(Procedure&);
    shared_ptr<ConditionExpression> ParseConditionExpression(Procedure&);

    std::string JoinWithDelimiter(std::vector<std::string>&, std::string);
};