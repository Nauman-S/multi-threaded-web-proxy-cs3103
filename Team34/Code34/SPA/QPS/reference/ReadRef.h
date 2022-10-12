#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class ReadRef : public StmtRef {
private:
    const AttrType default_attr_type_{ AttrType::kStmtNum };

public:
    using StmtRef::StmtRef;

    ReadRef(ValType val_type, std::string val)
        : StmtRef{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kReadRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }
};

