#include "StmtStmtRel.h"

#include <memory>
#include <string>
#include <vector>

#include "../DataRetriever.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


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
    vector<shared_ptr<Ref>> args = { lhs_ref_, rhs_ref_ };
    return Clause::CountSynonyms(args);
}

std::shared_ptr<std::vector<std::string>> StmtStmtRel::GetSynonyms()
{
    vector<shared_ptr<Ref>> args = { lhs_ref_, rhs_ref_ };
    return Clause::GetSynonyms(args);

}

std::shared_ptr<ResWrapper> StmtStmtRel::GetMatch(DataRetriever& retriever)
{
    return retriever.retrieve(*this);
}
