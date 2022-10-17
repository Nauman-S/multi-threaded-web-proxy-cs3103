#pragma once

#include <memory>

#include "../../PKB/WritePKBManager.h"

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
    NodeExtractor(std::shared_ptr<WritePKBManager> manager) : write_manager_(manager) {}

    virtual void ExtractProgramNode(const ProgramNode&) = 0;
    virtual void ExtractProcedureNode(const ProcedureASTNode&) = 0;

    virtual void ExtractAssignmentNode(const AssignStatementASTNode&) = 0;
    virtual void ExtractCallNode(const CallStatementASTNode&) = 0;
    virtual void ExtractPrintNode(const PrintStatementASTNode&) = 0;
    virtual void ExtractReadNode(const ReadStatementASTNode&) = 0;

    virtual void ExtractIfNode(const IfStatementASTNode&) = 0;
    virtual void ExtractWhileNode(const WhileStatementASTNode&) = 0;
    virtual void ExtractConditionExpression(const ConditionExpression&) = 0;

protected:
    std::shared_ptr<WritePKBManager> write_manager_;
};

