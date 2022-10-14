#pragma once

#include "StmtRef.h"
#include "../../Utils/type/RefType.h"

class DataRetriever;

class PrintRef : public StmtRef {
public:
    using StmtRef::StmtRef;

    const RefType GetRefType() override { return RefType::kPrintRef; }

    std::string GetAttrValue(DataRetriever& data_retriever, std::string& value) override;
};

