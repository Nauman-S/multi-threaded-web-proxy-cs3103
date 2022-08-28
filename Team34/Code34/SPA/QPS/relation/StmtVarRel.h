#pragma once
#include "Rel.h"
#include "../reference/StmtRef.h"
#include "../reference/VarRef.h"

class StmtVarRel :
    public Rel
{
protected:
    StmtRef lhs_ref_;
    VarRef rhs_ref_;

public:
    std::string LhsValue() override;

    std::string RhsValue() override;

    virtual std::optional<int> LhsValueAsInt();
};

