#pragma once
#include "StmtVarRel.h"
#include "RelType.h"

class ModifiesSRel :
    public StmtVarRel
{
public:
    using StmtVarRel::StmtVarRel;

    RelType GetRelType() override { return RelType::kModifiesSRel; }
};

