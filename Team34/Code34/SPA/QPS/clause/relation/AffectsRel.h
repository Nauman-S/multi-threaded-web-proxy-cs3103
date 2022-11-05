#pragma once
#include "StmtStmtRel.h"
#include "../ClauseType.h"

class AffectsRel
    :public StmtStmtRel {
public:
    using StmtStmtRel::StmtStmtRel;

    ClauseType GetRelType() override { return ClauseType::kAffectsRel; }

    Priority GetPriority(PriorityManager& pm) override;
};