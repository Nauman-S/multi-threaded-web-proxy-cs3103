#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class IfRef :
    public StmtRef
{
    using StmtRef::StmtRef;

public:
    const RefType GetRefType() override { return RefType::kIfRef; }
};

