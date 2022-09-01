#pragma once

#include <string>

#include "Rel.h"
#include "RelType.h"
#include "../reference/StmtRef.h"
#include "../reference/ValType.h"
#include "../query_result/ResWrapper.h"
#include "../DataRetriever.h"

class StmtStmtRel :
    public Rel
{
protected:
    StmtRef lhs_ref_;
    StmtRef rhs_ref_;

public:
    StmtStmtRel(StmtRef lhs, StmtRef rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    virtual std::optional<int> LhsValueAsInt();

    virtual std::optional<int> RhsValueAsInt();

    /*virtual std::unique_ptr<ResWrapper> GetMatch(DataRetriever& data_retriever) {
        return data_retriever.retrieve(*this);
    }*/

};

