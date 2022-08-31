#pragma once
#include "StmtStmtRel.h"
#include "RelType.h"

class ParentTRel :
    public StmtStmtRel
{
public:
    using StmtStmtRel::StmtStmtRel;

    RelType GetRelType() override { return RelType::kParentTRel; }
};

