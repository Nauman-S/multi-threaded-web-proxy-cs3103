#pragma once
#include "StmtVarRel.h"
#include "../ClauseType.h"

class ModifiesSRel :
    public StmtVarRel
{
public:
    using StmtVarRel::StmtVarRel;

    ClauseType GetRelType() override { return ClauseType::kModifiesSRel; }

    Priority GetPriority(PriorityManager& pm) override;
};

