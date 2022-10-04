#pragma once
#include "StmtStmtRel.h"
#include "../ClauseType.h"

class AffectsTRel
	:public StmtStmtRel
{
public:
	using StmtStmtRel::StmtStmtRel;

	ClauseType GetRelType() override { return ClauseType::kAffectsTRel; }

	Priority GetPriority(PriorityManager pm) override { return pm.GetClausePriority(ClauseType::kAffectsTRel); }
};
