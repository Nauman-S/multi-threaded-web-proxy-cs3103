#pragma once

# include <vector>
#include <string>
# include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class ConditionExpression : public StatementASTNode {
public:
    void SetVariables(std::vector<Variable>&);
    void SetConstants(std::vector<Constant>&);

    std::vector<Variable> GetVariables() const;
    std::vector<Constant> GetConstants() const;

    void Extract(NodeExtractor&) override;
    string Stringify() override;

protected:
    std::vector<Variable> vars;
    std::vector<Constant> cons;
};