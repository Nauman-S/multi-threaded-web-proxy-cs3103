#pragma once

#include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class PrintStatementASTNode : public StatementASTNode {
public:
    void SetVariable(Variable&);
    Variable GetVariable() const;

    virtual void Extract(NodeExtractor&) override;
    virtual string Stringify() override;

protected:
    Variable var;
};
