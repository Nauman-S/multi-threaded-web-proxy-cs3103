#include "StmtVarRel.h"

std::string StmtVarRel::LhsValue()
{
    return lhs_ref_.Value();
}

std::string StmtVarRel::RhsValue()
{
    return rhs_ref_.Value();
}

std::optional<int> StmtVarRel::LhsValueAsInt()
{
    return lhs_ref_.ValueAsInt();
}
