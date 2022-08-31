#include "StmtStmtRel.h"

std::string StmtStmtRel::LhsValue()
{
    return lhs_ref_.Value();
}

std::string StmtStmtRel::RhsValue()
{
    return rhs_ref_.Value();
}

std::optional<int> StmtStmtRel::LhsValueAsInt()
{
    return lhs_ref_.ValueAsInt();
}

std::optional<int> StmtStmtRel::RhsValueAsInt()
{
    return rhs_ref_.ValueAsInt();
}
