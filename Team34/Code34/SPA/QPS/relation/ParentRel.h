#pragma once
#include "StmtStmtRel.h"
#include "../ClauseType.h"

class ParentRel :
    public StmtStmtRel
{
public:
    using StmtStmtRel::StmtStmtRel;

    ClauseType GetRelType() override { return ClauseType::kParentRel; }

    Priority GetPriority(PriorityManager& pm) override;
};

