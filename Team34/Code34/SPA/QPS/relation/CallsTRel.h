#pragma once
#include "ProcProcRel.h"
#include "../ClauseType.h"

class CallsTRel
	:public ProcProcRel
{
public:
	using ProcProcRel::ProcProcRel;

	ClauseType GetRelType() override { return ClauseType::kCallsTRel; }

	Priority GetPriority(PriorityManager& pm) override;
};

