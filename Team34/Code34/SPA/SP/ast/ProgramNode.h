#pragma once

#include <vector>
#include <memory>
#include <map>

#include "ASTNode.h"
#include "ProcedureASTNode.h"
#include "../../Utils/type/TypeDef.h"

class ProgramNode : ASTNode {
public:
    ProgramNode();

    std::vector<std::shared_ptr<ProcedureASTNode>> GetChildren() const;
    std::map<Procedure, std::shared_ptr<ProcedureASTNode>> GetProcNodeMapping() const;

    void AddProcedure(std::shared_ptr<ProcedureASTNode>);

    virtual void Extract(NodeExtractor&) override;
    virtual string Stringify() override;

private:
    std::vector<std::shared_ptr<ProcedureASTNode>> children_;
    std::map<Procedure, std::shared_ptr<ProcedureASTNode>> proc_name_to_node_;
};
