#pragma once

#include <string>
#include <memory>

#include "Rel.h"
#include "../ClauseType.h"
#include "../reference/ProcRef.h"
#include "../reference/VarRef.h"
#include "../reference/ValType.h"
#include "../query_result/ResWrapper.h"
//#include "../DataRetriever.h"
class DataRetriever;


class ProcVarRel :
    public Rel
{
protected:
    std::shared_ptr<ProcRef> lhs_ref_;
    std::shared_ptr<VarRef> rhs_ref_;

public:
    ProcVarRel(std::shared_ptr<ProcRef> lhs, std::shared_ptr<VarRef> rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    ClauseType GetRelType() override { return ClauseType::kProcVarRel; }

    RefType LhsRefType() override;

    RefType RhsRefType() override;

    std::pair<ValType, ValType> ValTypes() override;

    std::shared_ptr<ResWrapper> GetMatch(DataRetriever& data_retriever) override;

    int CountSynonyms() override;

    virtual std::shared_ptr<std::vector<std::string>> GetSynonyms() override;
};

