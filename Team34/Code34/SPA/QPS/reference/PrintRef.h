#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class PrintRef : public StmtRef {
public:
    using StmtRef::StmtRef;

    const RefType GetRefType() override { return RefType::kPrintRef; }
};

