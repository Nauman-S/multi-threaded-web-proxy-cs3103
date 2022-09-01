#pragma once
#include "ProcVarRel.h"
#include "RelType.h"

class UsesPRel :
    public ProcVarRel
{
public:
    using ProcVarRel::ProcVarRel;

    RelType GetRelType() override { return RelType::kUsesPRel; }
};

