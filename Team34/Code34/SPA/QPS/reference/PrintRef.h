#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class PrintRef : public StmtRef {
private:
    const AttrType default_attr_type_{ AttrType::kStmtNum };

public:
    using StmtRef::StmtRef;

    PrintRef(ValType val_type, std::string val)
        : StmtRef{ val_type, val, default_attr_type_ } {
    };

    const RefType GetRefType() override { return RefType::kPrintRef; }

    bool IsAttrTypeDefault() override { return attr_type_ == default_attr_type_; }
};

