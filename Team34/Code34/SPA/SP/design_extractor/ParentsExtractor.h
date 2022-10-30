#pragma once

#include <memory>
#include <vector>

#include "NodeExtractor.h"

#include "../../PKB/WritePKBManager.h"
#include "../../Utils/type/TypeDef.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"
#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"
#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"
#include "../ast/ConditionExpression.h"

class ParentsExtractor : public NodeExtractor {
public:

    explicit ParentsExtractor(std::shared_ptr<WritePKBManager>);

    void ExtractProgramNode(const ProgramNode&) override;
    void ExtractProcedureNode(const ProcedureASTNode&) override;

    void ExtractAssignmentNode(const AssignStatementASTNode&) override;
    void ExtractCallNode(const CallStatementASTNode&) override;
    void ExtractPrintNode(const PrintStatementASTNode&) override;
    void ExtractReadNode(const ReadStatementASTNode&) override;

    void ExtractIfNode(const IfStatementASTNode&) override;
    void ExtractWhileNode(const WhileStatementASTNode&) override;
    void ExtractConditionExpression(const ConditionExpression&) override;

private:
    // Keeps track of parent statements in previous level as we go down
    // in nesting level
    std::vector<StmtNum> previous_parents_;

    void AddIndirectParents(StmtNum);
};
