#include "StmtStmtRel.h"
#include "../DataRetriever.h"

std::string StmtStmtRel::LhsValue()
{
    return lhs_ref_->GetName();
}

std::string StmtStmtRel::RhsValue()
{
    return rhs_ref_->GetName();
}

RefType StmtStmtRel::LhsRefType()
{
    return lhs_ref_->GetRefType();
}

RefType StmtStmtRel::RhsRefType()
{
    return rhs_ref_->GetRefType();
}

std::pair<ValType, ValType> StmtStmtRel::ValTypes()
{
    return std::pair<ValType, ValType>(lhs_ref_->GetValType(), rhs_ref_->GetValType());
}

std::optional<int> StmtStmtRel::LhsValueAsInt()
{
    return lhs_ref_->ValueAsInt();
}

std::optional<int> StmtStmtRel::RhsValueAsInt()
{
    return rhs_ref_->ValueAsInt();
}

int StmtStmtRel::CountSynonyms()
{
    int res = 0;
    if (lhs_ref_->GetValType() == ValType::kSynonym) {
        res += 1;
    }
    if (rhs_ref_->GetValType() == ValType::kSynonym) {
        res += 1;
    }

    return res;
}

std::shared_ptr<ResWrapper> StmtStmtRel::GetMatch(DataRetriever& retriever)
{
    return retriever.retrieve(*this);
}
