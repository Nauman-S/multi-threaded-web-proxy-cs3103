#pragma once
#include "StmtStmtRel.h"
#include "../ClauseType.h"

class FollowsRel :
    public StmtStmtRel
{
public:
    using StmtStmtRel::StmtStmtRel;

    ClauseType GetRelType() override { return ClauseType::kFollowsRel; }

    Priority GetPriority(PriorityManager pm) override;
};

