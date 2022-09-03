#include "StmtVarRel.h"
#include "../DataRetriever.h"

std::string StmtVarRel::LhsValue()
{
    return lhs_ref_.Value();
}

std::string StmtVarRel::RhsValue()
{
    return rhs_ref_.Value();
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
