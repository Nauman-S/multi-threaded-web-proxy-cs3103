#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class CallRef : public StmtRef {
private:
    const AttrType default_attr_type_{ AttrType::kStmtNum };

public:
    using StmtRef::StmtRef;

    CallRef(ValType val_type, std::string val)
        : StmtRef{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kCallRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }
};

