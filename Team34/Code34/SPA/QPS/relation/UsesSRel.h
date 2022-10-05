#pragma once

#include "StmtVarRel.h"
#include "../ClauseType.h"

class UsesSRel :
    public StmtVarRel
{
public:
    StmtVarRel::StmtVarRel;

    ClauseType GetRelType() override { return ClauseType::kUsesSRel; }

    Priority GetPriority(PriorityManager pm) override { return pm.GetClausePriority(ClauseType::kUsesSRel); }
};