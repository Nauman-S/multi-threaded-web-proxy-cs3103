#pragma once

class ProgramNode;
class ProcedureASTNode;
class AssignStatementASTNode;
class PrintStatementASTNode;
class ReadStatementASTNode;

class NodeExtractor {
public:
	virtual void ExtractProgramNode(ProgramNode&) = 0;
	virtual void ExtractProcedureNode(ProcedureASTNode&) = 0;
	virtual void ExtractAssignmentNode(AssignStatementASTNode&) = 0;
	virtual void ExtractPrintNode(PrintStatementASTNode&) = 0;
	virtual void ExtractReadNode(ReadStatementASTNode&) = 0;
};

