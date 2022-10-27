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

class UsesExtractor : public NodeExtractor {
public:
    UsesExtractor(std::shared_ptr<WritePKBManager>);

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
    std::map<Procedure, std::shared_ptr<ProcedureASTNode>> proc_node_map_;

    // Cache procedure to used variable in the procedure,
    // to prevent evaluating same procedure twice
    std::map<Procedure, std::shared_ptr<std::set<Variable>>> proc_uses_;
    bool IsExtractedProcedure(Procedure);
    void InitCachedSet(Procedure);

    // Add uses and modifies relationship from indirect parents (container
    // and call statements)
    std::vector<Procedure> proc_call_stack_;
    std::vector<StmtNum> parent_smts_;
    void SetIndirectUses(Variable);

    // Wrapper methods to access PKB API to write uses relationship
    void AddToUses(StmtNum, Variable);
    void AddToUses(Procedure, Variable);
};

