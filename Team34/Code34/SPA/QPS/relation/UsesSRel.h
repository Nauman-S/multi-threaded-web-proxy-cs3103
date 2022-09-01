#pragma once

#include "StmtVarRel.h"
#include "RelType.h"

class UsesSRel :
    public StmtVarRel
{
public:
    StmtVarRel::StmtVarRel;

    RelType GetRelType() override { return RelType::kUsesSRel; }
};

