#pragma once
#include "ProcProcRel.h"
#include "RelType.h"

class CallsRel
	:public ProcProcRel
{
public:
	using ProcProcRel::ProcProcRel;

	RelType GetRelType() override { return RelType::kCallsRel; }
};