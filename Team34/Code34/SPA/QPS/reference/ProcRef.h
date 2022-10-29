#pragma once

#include <memory>
#include <string>

#include "Ref.h"
#include "../../Utils/type/RefType.h"

class ProcRef : public Ref {
private:
    static const AttrType default_attr_type_{ AttrType::kProcName };

public:
    using Ref::Ref;

    ProcRef(ValType val_type, std::string val)
        : Ref{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kProcRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }

    AttrType GetDefaultAttrType() override { return default_attr_type_; }

    std::shared_ptr<Ref> Clone() override { return std::make_shared<ProcRef>(*this); }
};

