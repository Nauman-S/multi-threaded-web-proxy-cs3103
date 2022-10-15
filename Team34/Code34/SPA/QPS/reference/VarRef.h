#pragma once

#include "Ref.h"
#include "../../Utils/type/RefType.h"

class VarRef : public Ref {
private:
    static const AttrType default_attr_type_{ AttrType::kVarName };

public:
    using Ref::Ref;

    VarRef(ValType val_type, std::string val)
        : Ref{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kVarRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }

    AttrType GetDefaultAttrType() override { return default_attr_type_; }

    inline std::string TestString() { return "This is a VarRef"; }
};