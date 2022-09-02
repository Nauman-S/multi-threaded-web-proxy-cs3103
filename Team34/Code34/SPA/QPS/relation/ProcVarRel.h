#pragma once

#include <string>
#include <memory>

#include "Rel.h"
#include "RelType.h"
#include "../reference/ProcRef.h"
#include "../reference/VarRef.h"
#include "../reference/ValType.h"
//#include "../query_result/ResWrapper.h"
//#include "../DataRetriever.h"

class ProcVarRel :
    public Rel
{
protected:
    ProcRef lhs_ref_;
    VarRef rhs_ref_;

public:
    ProcVarRel(ProcRef lhs, VarRef rhs) : lhs_ref_(lhs), rhs_ref_(rhs) {};

    std::string LhsValue() override;

    std::string RhsValue() override;

    std::pair<ValType, ValType> ValTypes() override;

    RelType GetRelType() override { return RelType::kProcVarRel; }

    /*virtual std::unique_ptr<ResWrapper> GetMatch(DataRetriever& data_retriever) {
        return data_retriever.retrieve(*this);
    }*/
};

