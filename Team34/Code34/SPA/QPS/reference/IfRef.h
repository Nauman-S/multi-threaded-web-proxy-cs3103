#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class IfRef : public StmtRef {
private:
    const AttrType default_attr_type_{ AttrType::kStmtNum };

public:
    using StmtRef::StmtRef;

    IfRef(ValType val_type, std::string val)
        : StmtRef{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kIfRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }
};

