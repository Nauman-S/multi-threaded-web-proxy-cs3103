#pragma once

#include <memory>
#include <set>

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

    NextExtractor(std::shared_ptr<WritePKBManager>);

    virtual void ExtractProgramNode(const ProgramNode&) override;
    virtual void ExtractProcedureNode(const ProcedureASTNode&) override;

    virtual void ExtractAssignmentNode(const AssignStatementASTNode&) override;
    virtual void ExtractCallNode(const CallStatementASTNode&) override;
    virtual void ExtractPrintNode(const PrintStatementASTNode&) override;
    virtual void ExtractReadNode(const ReadStatementASTNode&) override;

    virtual void ExtractIfNode(const IfStatementASTNode&) override;
    virtual void ExtractWhileNode(const WhileStatementASTNode&) override;
    virtual void ExtractConditionExpression(const ConditionExpression&) override;

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
