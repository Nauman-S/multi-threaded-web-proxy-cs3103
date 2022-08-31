#pragma once
#include "Rel.h"
#include "../reference/StmtRef.h"
#include "../reference/ValType.h"
#include "RelType.h"

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

    std::pair<ValType, ValType> ValTypes() override;

    RelType GetRelType() override { return RelType::kStmtStmtRel; }

    virtual std::optional<int> LhsValueAsInt();

    virtual std::optional<int> RhsValueAsInt();

};

