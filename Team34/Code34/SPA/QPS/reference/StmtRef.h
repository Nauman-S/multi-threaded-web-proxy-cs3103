#pragma once

#include <optional>
#include <string>
#include <memory>

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

    AttrType GetDefaultAttrType() override { return default_attr_type_; }

    std::shared_ptr<Ref> Clone() override { return std::make_shared<StmtRef>(*this); };
};

