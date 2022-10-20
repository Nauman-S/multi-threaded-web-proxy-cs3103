#include "Ref.h"
#include "../../Utils/type/RefType.h"

class TempRef : public Ref {
public:
    using Ref::Ref;

    TempRef(ValType val_type, std::string val)
        : Ref{ val_type, val, AttrType::kConst } {
    };

    const RefType GetRefType() override { return RefType::kUnknown; }

    bool IsAttrTypeDefault() override { return true; }

    AttrType GetDefaultAttrType() override { return AttrType::kConst; }

    std::shared_ptr<Ref> Clone() override { return std::make_shared<TempRef>(*this); }
};
