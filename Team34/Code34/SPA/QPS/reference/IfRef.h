#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class IfRef : public StmtRef {
public:
    using StmtRef::StmtRef;

    const RefType GetRefType() override { return RefType::kIfRef; }

    std::shared_ptr<Ref> Clone() override { return std::make_shared<IfRef>(*this); }
};

