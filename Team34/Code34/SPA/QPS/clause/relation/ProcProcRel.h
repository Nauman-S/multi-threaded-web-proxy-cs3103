#pragma once

#include <string>
#include <memory>

#include "Rel.h"
#include "../ClauseType.h"
#include "../../reference/ProcRef.h"
#include "../../reference/ValType.h"
#include "../../query_result/ResWrapper.h"
class DataRetriever;

class ProcProcRel
	: public Rel
{
protected:
	std::shared_ptr<ProcRef> lhs_ref_;
	std::shared_ptr<ProcRef> rhs_ref_;

public:
    ProcProcRel(std::shared_ptr<ProcRef> lhs, std::shared_ptr<ProcRef> rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    ClauseType GetRelType() override { return ClauseType::kProcProcRel; }

    RefType LhsRefType() override;

    RefType RhsRefType() override;

    std::pair<ValType, ValType> ValTypes() override;

    std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;

    int CountSynonyms() override;

    std::shared_ptr<std::vector<std::string>> GetSynonyms() override;

};