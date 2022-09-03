#include "StmtStmtRel.h"
#include "../DataRetriever.h"

std::string StmtStmtRel::LhsValue()
{
    return lhs_ref_.Value();
}

std::string StmtStmtRel::RhsValue()
{
    return rhs_ref_.Value();
}

std::pair<ValType, ValType> StmtStmtRel::ValTypes()
{
    return std::pair<ValType, ValType>(lhs_ref_.GetValType(), rhs_ref_.GetValType());
}

std::optional<int> StmtStmtRel::LhsValueAsInt()
{
    return lhs_ref_.ValueAsInt();
}

std::optional<int> StmtStmtRel::RhsValueAsInt()
{
    return rhs_ref_.ValueAsInt();
}

//std::unique_ptr<ResWrapper> StmtStmtRel::GetMatch(DataRetriever& data_retriever)
//{
//    return data_retriever.retrieve(*this);
//}