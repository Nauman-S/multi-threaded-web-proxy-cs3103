#pragma once

#include <memory>
#include <string>

#include "IntValueableRef.h"
#include "../../Utils/type/RefType.h"

class ConstRef : public IntValueableRef {
private:
    static const AttrType default_attr_type_{ AttrType::kConst };

public:
    using IntValueableRef::IntValueableRef;

    ConstRef(ValType val_type, std::string val)
        : IntValueableRef{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kConstRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }

    AttrType GetDefaultAttrType() override { return default_attr_type_; }

    std::shared_ptr<Ref> Clone() override { return std::make_shared<ConstRef>(*this);
    }
};

