#pragma once
#include "ProcProcRel.h"
#include "RelType.h"

class CallsTRel
	:public ProcProcRel
{
public:
	using ProcProcRel::ProcProcRel;

	RelType GetRelType() override { return RelType::kCallsTRel; }
};
