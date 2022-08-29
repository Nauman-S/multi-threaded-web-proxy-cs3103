#pragma once
#include "StmtRef.h"
#include "RefType.h"

class AssignRef :
    public StmtRef
{
    using StmtRef::StmtRef;

public:
    const RefType GetRefType() override { return RefType::kAssignRef; }
};

