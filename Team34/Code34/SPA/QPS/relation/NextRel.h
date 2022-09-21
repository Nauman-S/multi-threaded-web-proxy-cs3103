#pragma once
#include "StmtStmtRel.h"
#include "RelType.h"

class NextRel
	:public StmtStmtRel
{
public:
	using StmtStmtRel::StmtStmtRel;

	RelType GetRelType() override { return RelType::kNextRel; }
};