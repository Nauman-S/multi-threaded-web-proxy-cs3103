#pragma once

#include <memory>
#include <vector>
#include <set>
#include <map>
#include <utility>

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

class CallsExtractor : public NodeExtractor {
public:
    explicit CallsExtractor(std::shared_ptr<WritePKBManager>);

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
    // Map of procedure to set of Calls* relation for that procedure, used as cache
    // to prevent evaluating same procedure twice
    std::map<Procedure, std::shared_ptr<std::set<Procedure>>> proc_to_calls_T_;
    void AddToCachedSet(Procedure);
    bool IsExtractedProcedure(Procedure);
    void InitCachedSet(Procedure);

    std::map<Procedure, std::shared_ptr<ProcedureASTNode>> proc_node_map_;
    std::vector<Procedure> procedure_calls_stack_;

    // Wrapper methods to access write PKB API
    void AddToCalls(Procedure, Procedure);
    void AddToCallsT(Procedure, Procedure);
};
