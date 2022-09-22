#pragma once
#include "StmtStmtRel.h"
#include "RelType.h"

class AffectsTRel
	:public StmtStmtRel
{
public:
	using StmtStmtRel::StmtStmtRel;

	RelType GetRelType() override { return RelType::kAffectsTRel; }
};
