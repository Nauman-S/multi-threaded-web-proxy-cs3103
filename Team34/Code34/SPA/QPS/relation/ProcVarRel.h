#pragma once
#include "Rel.h"
#include "../reference/ProcRef.h"
#include "../reference/VarRef.h"

#include <string>

class ProcVarRel :
    public Rel
{
protected:
    ProcRef lhs_ref_;
    VarRef rhs_ref_;

public:
    ProcVarRel(ProcRef lhs, VarRef rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;
};

