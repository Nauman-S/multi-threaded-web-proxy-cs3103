#include "StmtVarRel.h"
#include "../DataRetriever.h"

std::string StmtVarRel::LhsValue()
{
    return lhs_ref_.GetName();
}

std::string StmtVarRel::RhsValue()
{
    return rhs_ref_.GetName();
}

RefType StmtVarRel::LhsRefType()
{
    return lhs_ref_.GetRefType();
}

RefType StmtVarRel::RhsRefType()
{
    return rhs_ref_.GetRefType();
}


std::pair<ValType, ValType> StmtVarRel::ValTypes()
{
    return std::pair<ValType, ValType>(lhs_ref_.GetValType(), rhs_ref_.GetValType());
}

std::optional<int> StmtVarRel::LhsValueAsInt()
{
    return lhs_ref_.ValueAsInt();
}

std::shared_ptr<ResWrapper> StmtVarRel::GetMatch(DataRetriever& retriever)
{
    return retriever.retrieve(*this);
}
