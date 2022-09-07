#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class WhileRef :
    public StmtRef
{
    using StmtRef::StmtRef;

public:
    const RefType GetRefType() override { return RefType::kWhileRef; }
};

