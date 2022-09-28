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
	std::shared_ptr<ProgramNode> Parse(std::string&);

	std::shared_ptr<ProcedureASTNode> ParseProcedure(std::vector<SourceToken>, int&, int&);

	std::shared_ptr<StatementASTNode> ParseStatement(std::vector<SourceToken>, int&, int&, Procedure&);

	std::shared_ptr<CallStatementASTNode> ParseCallStatement(std::vector<SourceToken>, int&, int&, Procedure&);

	std::shared_ptr<ReadStatementASTNode> ParseReadStatement(std::vector<SourceToken>, int&, int&, Procedure&);

	std::shared_ptr<PrintStatementASTNode> ParsePrintStatement(std::vector<SourceToken>, int&, int&, Procedure&);

	std::shared_ptr<IfStatementASTNode> ParseIfStatement(std::vector<SourceToken>, int&, int&, Procedure&);

	std::shared_ptr<WhileStatementASTNode> ParseWhileStatement(std::vector<SourceToken>, int&, int&, Procedure&);

	std::shared_ptr<AssignStatementASTNode> ParseAssignStatement(std::vector<SourceToken>, int&, int&, Procedure&);

	std::shared_ptr<ConditionExpression> ParseConditionExpression(std::vector<SourceToken>, int&, int&, Procedure&);

	static inline std::map<Procedure, std::shared_ptr<ProcedureASTNode>> proc_name_to_node_;

private:
	std::string JoinWithDelimiter(std::vector<std::string>&, std::string);
};