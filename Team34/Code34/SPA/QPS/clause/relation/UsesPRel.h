#pragma once

#include "ProcVarRel.h"
#include "../ClauseType.h"

class UsesPRel :
    public ProcVarRel {
public:
    using ProcVarRel::ProcVarRel;

    ClauseType GetRelType() override { return ClauseType::kUsesPRel; }

    Priority GetPriority(PriorityManager& pm) override;
};

