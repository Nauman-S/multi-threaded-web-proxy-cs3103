#pragma once

#include <memory>

#include "Rel.h"
#include "RelType.h"
#include "../reference/StmtRef.h"
#include "../reference/VarRef.h"
#include "../reference/ValType.h"
#include "../query_result/ResWrapper.h"
//#include "../DataRetriever.h"
class DataRetriever;  // forward declaration to avoid cyclic include of Visitor pattern

class StmtVarRel :
    public Rel
{
protected:
    StmtRef lhs_ref_;
    VarRef rhs_ref_;

public:
    StmtVarRel(StmtRef lhs, VarRef rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    std::pair<ValType, ValType> ValTypes() override;

    RelType GetRelType() override { return RelType::kStmtVarRel; }

    virtual std::optional<int> LhsValueAsInt();

    std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;
};

