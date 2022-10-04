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
    std::shared_ptr<StmtRef> lhs_ref_;
    std::shared_ptr <VarRef> rhs_ref_;

public:
    StmtVarRel(std::shared_ptr<StmtRef> lhs, std::shared_ptr<VarRef> rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    RelType GetRelType() override { return RelType::kStmtVarRel; }

    RefType LhsRefType() override;

    RefType RhsRefType() override;

    std::pair<ValType, ValType> ValTypes() override;

    std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;

    int CountSynonyms() override;

    virtual std::optional<int> LhsValueAsInt();

    
};

