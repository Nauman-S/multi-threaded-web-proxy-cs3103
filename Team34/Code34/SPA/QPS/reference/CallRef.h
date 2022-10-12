#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class CallRef : public StmtRef {
public:
    using StmtRef::StmtRef;

    const RefType GetRefType() override { return RefType::kCallRef; }
};

