#pragma once

#include <string>

# include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class CallStatementASTNode : public StatementASTNode {
public:
    void SetProcedure(Procedure& p);
    Procedure GetProcedure() const;

    void Extract(NodeExtractor&) override;
    string Stringify() override;

protected:
    Procedure proc;
};
