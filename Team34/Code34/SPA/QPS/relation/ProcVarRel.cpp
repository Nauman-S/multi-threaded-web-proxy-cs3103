#include "ProcVarRel.h"

#include <memory>
#include <string>
#include <vector>

#include "../DataRetriever.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


std::string ProcVarRel::LhsValue() {
    return lhs_ref_->GetName();
}

std::string ProcVarRel::RhsValue() {
    return rhs_ref_->GetName();
}

RefType ProcVarRel::LhsRefType()
{
    return lhs_ref_->GetRefType();
}

RefType ProcVarRel::RhsRefType()
{
    return rhs_ref_->GetRefType();
}

std::pair<ValType, ValType> ProcVarRel::ValTypes() {
    return std::pair<ValType, ValType>(lhs_ref_->GetValType(), rhs_ref_->GetValType());
}

std::shared_ptr<ResWrapper> ProcVarRel::GetMatch(DataRetriever& data_retriever) {
    return data_retriever.retrieve(*this);
}

int ProcVarRel::CountSynonyms()
{
    vector<shared_ptr<Ref>>& args = { lhs_ref_, rhs_ref_ };
    return Clause::CountSynonyms(args);
}

std::shared_ptr<std::vector<std::string>> ProcVarRel::GetSynonyms()
{
    vector<shared_ptr<Ref>>& args = { lhs_ref_, rhs_ref_ };
    return Clause::GetSynonyms(args);
}
