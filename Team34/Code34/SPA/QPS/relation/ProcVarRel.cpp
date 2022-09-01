#include "ProcVarRel.h"

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
