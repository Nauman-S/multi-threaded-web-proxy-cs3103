#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class WhileRef : public StmtRef {
public:
    using StmtRef::StmtRef;

    const RefType GetRefType() override { return RefType::kWhileRef; }

    std::shared_ptr<Ref> Clone() override { return std::make_shared<WhileRef>(*this); }
};

