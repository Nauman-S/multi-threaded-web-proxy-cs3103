#pragma once

#include <string>
#include <memory>

#include "Rel.h"
#include "../ClauseType.h"
#include "../reference/StmtRef.h"
#include "../reference/ValType.h"
#include "../query_result/ResWrapper.h"
//#include "../DataRetriever.h"
class DataRetriever;  // To avoid cyclic include of visitor pattern

class StmtStmtRel :
    public Rel
{
protected:
    std::shared_ptr<StmtRef> lhs_ref_;
    std::shared_ptr<StmtRef> rhs_ref_;

public:
    StmtStmtRel(std::shared_ptr<StmtRef> lhs, std::shared_ptr<StmtRef> rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    ClauseType GetRelType() override { return ClauseType::kStmtStmtRel; }

    RefType LhsRefType() override;

    RefType RhsRefType() override;

    std::pair<ValType, ValType> ValTypes() override;

    std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;

    int CountSynonyms() override;

    virtual std::optional<int> LhsValueAsInt();

    virtual std::optional<int> RhsValueAsInt();

};

