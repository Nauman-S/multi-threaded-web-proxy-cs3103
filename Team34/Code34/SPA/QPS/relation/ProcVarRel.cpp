#include "ProcVarRel.h"
#include "../DataRetriever.h"

std::string ProcVarRel::LhsValue()
{
    return lhs_ref_.Value();
}

std::string ProcVarRel::RhsValue()
{
    return rhs_ref_.Value();
}

std::pair<ValType, ValType> ProcVarRel::ValTypes()
{
    return std::pair<ValType, ValType>(lhs_ref_.GetValType(), rhs_ref_.GetValType());
}

std::unique_ptr<ResWrapper> ProcVarRel::GetMatch(DataRetriever& data_retriever)
{
    return data_retriever.retrieve(*this);
}