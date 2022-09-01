#pragma once
#include "StmtStmtRel.h"
#include "RelType.h"

class ParentRel :
    public StmtStmtRel
{
public:
    using StmtStmtRel::StmtStmtRel;

    RelType GetRelType() override { return RelType::kParentRel; }
};

