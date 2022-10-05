#pragma once
#include "ProcVarRel.h"
#include "../ClauseType.h"

class ModifiesPRel :
    public ProcVarRel
{
public:
    using ProcVarRel::ProcVarRel;

    ClauseType GetRelType() { return ClauseType::kModifiesPRel; }

    Priority GetPriority(PriorityManager& pm) override;
};

