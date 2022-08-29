#pragma once
#include "IntValueableRef.h"
#include "../../Utils/type/RefType.h"

#include <optional>

class StmtRef :
    public IntValueableRef
{
    using IntValueableRef::IntValueableRef;

public:
    const RefType GetRefType() override { return RefType::kStmtRef; }
};

