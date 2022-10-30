#pragma once

#include <memory>
#include <set>
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

class NextExtractor : public NodeExtractor {
public:

    explicit NextExtractor(std::shared_ptr<WritePKBManager>);

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
    void SetDirectEdge(StmtNum);
    void SetBlockEdge(StmtNum);

    std::set<StmtNum> prev_stmts_;
    void AddPrevStmt(StmtNum);
    void ClearPrevStmts();

    std::set<StmtNum> prev_blocks_;
    StmtNum block_start_stmt_ = 0;
    StmtNum block_end_stmt_ = 0;
    bool is_block_end_ = true;

    void AddPrevBlockStart(StmtNum);
    void ClearPrevBlocks();
    void CreateBlock();
    void MarkBlockEnd();

    void AddNextRelation(StmtNum);
};
