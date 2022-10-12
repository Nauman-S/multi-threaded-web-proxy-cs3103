#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class AssignRef : public StmtRef {
public:
    using StmtRef::StmtRef;

    const RefType GetRefType() override { return RefType::kAssignRef; }
};

