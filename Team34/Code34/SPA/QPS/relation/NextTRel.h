#pragma once
#include "StmtStmtRel.h"
#include "RelType.h"

class NextTRel
	:public StmtStmtRel
{
public:
	using StmtStmtRel::StmtStmtRel;

	RelType GetRelType() override { return RelType::kNextTRel; }
};