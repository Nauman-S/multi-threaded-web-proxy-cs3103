#pragma once
#include "StmtStmtRel.h"
#include "RelType.h"

class FollowsRel :
    public StmtStmtRel
{
public:
    using StmtStmtRel::StmtStmtRel;

    RelType GetRelType() override { return RelType::kFollowsRel; }
};

