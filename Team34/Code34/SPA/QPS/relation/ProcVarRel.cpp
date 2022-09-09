#include "ProcVarRel.h"
#include "../DataRetriever.h"


std::string ProcVarRel::LhsValue() {
    return lhs_ref_.GetName();
}

std::string ProcVarRel::RhsValue() {
    return rhs_ref_.GetName();
}

RefType ProcVarRel::LhsRefType()
{
    return lhs_ref_.GetRefType();
}

RefType ProcVarRel::RhsRefType()
{
    return rhs_ref_.GetRefType();
}

std::pair<ValType, ValType> ProcVarRel::ValTypes() {
    return std::pair<ValType, ValType>(lhs_ref_.GetValType(), rhs_ref_.GetValType());
}

std::shared_ptr<ResWrapper> ProcVarRel::GetMatch(DataRetriever& data_retriever) {
    return data_retriever.retrieve(*this);
}
