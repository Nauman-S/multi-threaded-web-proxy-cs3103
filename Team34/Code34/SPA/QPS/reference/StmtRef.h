#pragma once

#include <optional>

#include "IntValueableRef.h"
#include "../../Utils/type/RefType.h"

class StmtRef :
    public IntValueableRef
{
    using IntValueableRef::IntValueableRef;

public:
    const RefType GetRefType() override { return RefType::kStmtRef; }
};

