#pragma once
#include "Ref.h"
#include "../../Utils/type/RefType.h"

class VarRef :
    public Ref
{
    using Ref::Ref;

public:
    const RefType GetRefType() override { return RefType::kVarRef;  }
};