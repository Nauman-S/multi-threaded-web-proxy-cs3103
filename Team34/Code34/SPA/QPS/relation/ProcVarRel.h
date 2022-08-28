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
    std::string LhsValue() override;

    std::string RhsValue() override;
};

