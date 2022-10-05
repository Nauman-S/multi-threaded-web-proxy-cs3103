#pragma once
#include "StmtStmtRel.h"
#include "../ClauseType.h"

class NextRel
	:public StmtStmtRel
{
public:
	using StmtStmtRel::StmtStmtRel;

	ClauseType GetRelType() override { return ClauseType::kNextRel; }

	Priority GetPriority(PriorityManager& pm) override;
};