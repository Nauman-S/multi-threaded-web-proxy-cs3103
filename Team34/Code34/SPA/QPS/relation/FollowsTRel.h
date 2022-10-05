#pragma once
#include "StmtStmtRel.h"
#include "../ClauseType.h"

class FollowsTRel :
    public StmtStmtRel
{
public:
    using StmtStmtRel::StmtStmtRel;

    ClauseType GetRelType() override { return ClauseType::kFollowsTRel; }

    Priority GetPriority(PriorityManager pm) override;
};

