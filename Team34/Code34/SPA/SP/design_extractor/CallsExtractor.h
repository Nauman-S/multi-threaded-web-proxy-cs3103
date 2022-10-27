#pragma once

#include <memory>
#include <vector>
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

class CallsExtractor : public NodeExtractor {
public:
    CallsExtractor(std::shared_ptr<WritePKBManager>);

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
