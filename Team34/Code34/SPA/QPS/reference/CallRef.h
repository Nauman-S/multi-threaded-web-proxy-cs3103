#pragma once
#include <memory>
#include <string>
#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class DataRetriever;

class CallRef : public StmtRef {
public:
    using StmtRef::StmtRef;

    const RefType GetRefType() override { return RefType::kCallRef; }

    std::string GetAttrValue(DataRetriever& data_retriever, std::string& value) override;

    std::shared_ptr<Ref> Clone() override { return std::make_shared<CallRef>(*this); }
};

