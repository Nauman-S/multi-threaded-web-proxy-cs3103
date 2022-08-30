#pragma once

#include "Rel.h"
#include "../reference/StmtRef.h"
#include "../reference/VarRef.h"
#include "../reference/ValType.h"

class StmtVarRel :
    public Rel
{
protected:
    StmtRef lhs_ref_;
    VarRef rhs_ref_;

public:
    StmtVarRel(StmtRef lhs, VarRef rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    std::pair<ValType, ValType> ValTypes() override;

    virtual std::optional<int> LhsValueAsInt();
};

