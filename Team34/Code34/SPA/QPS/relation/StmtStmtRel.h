#pragma once

#include <string>

#include "Rel.h"
#include "RelType.h"
#include "../reference/StmtRef.h"
#include "../reference/ValType.h"
#include "../query_result/ResWrapper.h"
//#include "../DataRetriever.h"
class DataRetriever;  // To avoid cyclic include of visitor pattern

class StmtStmtRel :
    public Rel
{
protected:
    StmtRef& lhs_ref_;
    StmtRef& rhs_ref_;

public:
    StmtStmtRel(StmtRef& lhs, StmtRef& rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    std::pair<ValType, ValType> ValTypes() override;

    RelType GetRelType() override { return RelType::kStmtStmtRel; }

    std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;

    virtual std::optional<int> LhsValueAsInt();

    virtual std::optional<int> RhsValueAsInt();

    virtual RefType LhsRefType() { return lhs_ref_.GetRefType(); }

    virtual RefType RhsRefType() { return rhs_ref_.GetRefType(); }

    
};

