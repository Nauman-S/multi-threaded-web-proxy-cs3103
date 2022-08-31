#pragma once
#include "StmtStmtRel.h"
#include "RelType.h"

class FollowsTRel :
    public StmtStmtRel
{
public:
    using StmtStmtRel::StmtStmtRel;

    RelType GetRelType() override { return RelType::kFollowsTRel; }
};

