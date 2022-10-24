#pragma once
#include "StmtStmtRel.h"
#include "../ClauseType.h"

class ParentTRel :
    public StmtStmtRel
{
public:
    using StmtStmtRel::StmtStmtRel;

    ClauseType GetRelType() override { return ClauseType::kParentTRel; }

    Priority GetPriority(PriorityManager& pm) override;
};

