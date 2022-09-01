#pragma once
#include "ProcVarRel.h"
#include "RelType.h"

class ModifiesPRel :
    public ProcVarRel
{
public:
    using ProcVarRel::ProcVarRel;

    RelType GetRelType() { return RelType::kModifiesPRel; }
};

