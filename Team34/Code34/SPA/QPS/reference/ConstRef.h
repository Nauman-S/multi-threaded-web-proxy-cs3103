#pragma once

#include "IntValueableRef.h"
#include "../../Utils/type/RefType.h"

class ConstRef : public IntValueableRef {
private:
    const AttrType default_attr_type_{ AttrType::kConst };

public:
    using IntValueableRef::IntValueableRef;

    ConstRef(ValType val_type, std::string val)
        : IntValueableRef{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kConstRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }
};

