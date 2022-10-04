#pragma once
#include "ProcProcRel.h"
#include "../ClauseType.h"

class CallsRel
	:public ProcProcRel
{
public:
	using ProcProcRel::ProcProcRel;

	ClauseType GetRelType() override { return ClauseType::kCallsRel; }

	Priority GetPriority(PriorityManager pm) override { return pm.GetClausePriority(ClauseType::kCallsRel); }
};