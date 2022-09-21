#pragma once
#include "StmtStmtRel.h"
#include "RelType.h"

class AffectsRel
	:public StmtStmtRel
{
public:
	using StmtStmtRel::StmtStmtRel;

	RelType GetRelType() override { return RelType::kAffectsRel; }
};