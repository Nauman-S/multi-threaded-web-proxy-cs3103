#pragma once

#include <optional>

#include "IntValueableRef.h"
#include "../../Utils/type/RefType.h"

class StmtRef : public IntValueableRef {
public:
    using IntValueableRef::IntValueableRef;

    StmtRef(ValType val_type, std::string val)
        : IntValueableRef{ val_type, val, AttrType::kStmtNum } {
    };

    const RefType GetRefType() override { return RefType::kStmtRef; }

    bool IsAttrTypeDefault() override { return true; }
};

