#pragma once

#include <string>
#include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

using namespace std;

class ReadStatementASTNode : public StatementASTNode {
public:
    void SetVariable(Variable&);
    virtual Variable GetReadVariable() const;

    void Extract(NodeExtractor&) override;
    string Stringify() override;

protected:
    Variable var;
};
