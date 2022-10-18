#pragma once

#include <string>
#include <vector>

#include "ASTNode.h"
#include "../../Utils/type/TypeDef.h"

class StatementASTNode : public ASTNode {
public:
    void SetLineIndex(StmtNum&);
    StmtNum GetLineIndex() const;

    void SetParentSatementLineIndex(StmtNum&);
    StmtNum GetParentSatementLineIndex() const;

    void SetParentProcIndex(Procedure&);
    Procedure GetParentProcIndex() const;

    virtual void Extract(NodeExtractor&) = 0;
    virtual string Stringify() = 0;

    bool operator < (const StatementASTNode& c) const {
        return lineIndex < c.lineIndex;
    }

protected:
    StmtNum lineIndex;
    StmtNum parent_stmt;
    Procedure parent_proc;
};