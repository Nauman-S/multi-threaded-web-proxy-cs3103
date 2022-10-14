#pragma once

#include <optional>

#include "IntValueableRef.h"
#include "../../Utils/type/RefType.h"

class StmtRef : public IntValueableRef {

protected:
    static const AttrType default_attr_type_{ AttrType::kStmtNum };

public:
    using IntValueableRef::IntValueableRef;

    StmtRef(ValType val_type, std::string val)
        : IntValueableRef{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kStmtRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }
};

