#pragma once
#include "StmtStmtRel.h"
#include "../ClauseType.h"

class NextTRel
	:public StmtStmtRel
{
public:
	using StmtStmtRel::StmtStmtRel;

	ClauseType GetRelType() override { return ClauseType::kNextTRel; }

	Priority GetPriority(PriorityManager pm) override { return pm.GetClausePriority(ClauseType::kNextTRel); }
};