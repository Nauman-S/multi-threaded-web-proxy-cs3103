#pragma once

#include <memory>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <map>

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

class ModifiesExtractor : public NodeExtractor {
public:
    explicit ModifiesExtractor(std::shared_ptr<WritePKBManager>);

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
    std::map<Procedure, std::shared_ptr<ProcedureASTNode>> proc_node_map_;

    // Cache procedure to modified variable in the procedure,
    // to prevent evaluating same procedure twice
    std::map<Procedure, std::shared_ptr<std::set<Variable>>> proc_modifies_;
    bool IsExtractedProcedure(Procedure);
    void InitCachedSet(Procedure);

    // Add modifies relationship from indirect parents (container
    // and call statements)
    std::vector<Procedure> proc_call_stack_;
    std::vector<StmtNum> parent_smts_;
    void SetIndirectModifies(Variable);

    // Wrapper methods to access PKB API to write modifies relationship
    void AddToModifies(StmtNum, Variable);
    void AddToModifies(Procedure, Variable);
};

