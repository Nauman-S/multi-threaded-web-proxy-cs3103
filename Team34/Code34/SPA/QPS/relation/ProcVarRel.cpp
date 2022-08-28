#include "ProcVarRel.h"

std::string ProcVarRel::LhsValue()
{
    return lhs_ref_.Value();
}

std::string ProcVarRel::RhsValue()
{
    return rhs_ref_.Value();
}
