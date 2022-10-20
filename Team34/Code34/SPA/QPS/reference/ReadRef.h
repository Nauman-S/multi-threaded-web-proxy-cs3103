#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class DataRetriever;

class ReadRef : public StmtRef {
public:
    using StmtRef::StmtRef;

    const RefType GetRefType() override { return RefType::kReadRef; }

    std::string GetAttrValue(DataRetriever& data_retriever, std::string& value) override;

    std::shared_ptr<Ref> Clone() override { return std::make_shared<ReadRef>(*this); }
};

