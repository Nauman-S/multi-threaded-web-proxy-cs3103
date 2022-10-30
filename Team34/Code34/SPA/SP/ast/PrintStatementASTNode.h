#pragma once

#include <string>
#include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class PrintStatementASTNode : public StatementASTNode {
public:
    void SetVariable(Variable&);
    Variable GetVariable() const;

    void Extract(NodeExtractor&) override;
    string Stringify() override;

protected:
    Variable var;
};
