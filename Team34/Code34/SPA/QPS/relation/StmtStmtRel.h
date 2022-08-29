#pragma once
#include "Rel.h"
#include "../reference/StmtRef.h"

#include <string>

class StmtStmtRel :
    public Rel
{
protected:
    StmtRef lhs_ref_;
    StmtRef rhs_ref_;

public:
    StmtStmtRel(StmtRef lhs, StmtRef rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    virtual std::optional<int> LhsValueAsInt();

    virtual std::optional<int> RhsValueAsInt();

};

