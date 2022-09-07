#pragma once

// Forward declaration to prevent cyclic inclusion
class ProgramNode;
class ProcedureASTNode;

class AssignStatementASTNode;
class CallStatementASTNode;
class PrintStatementASTNode;
class ReadStatementASTNode;

class IfStatementASTNode;
class WhileStatementASTNode;
class ConditionExpression;

class NodeExtractor {
public:
	virtual void ExtractProgramNode(ProgramNode&) = 0;
	virtual void ExtractProcedureNode(ProcedureASTNode&) = 0;

	virtual void ExtractAssignmentNode(AssignStatementASTNode&) = 0;
	virtual void ExtractCallNode(CallStatementASTNode&) = 0;
	virtual void ExtractPrintNode(PrintStatementASTNode&) = 0;
	virtual void ExtractReadNode(ReadStatementASTNode&) = 0;

	virtual void ExtractIfNode(IfStatementASTNode&) = 0;
	virtual void ExtractWhileNode(WhileStatementASTNode&) = 0;
	virtual void ExtractConditionExpression(ConditionExpression&) = 0;
};

