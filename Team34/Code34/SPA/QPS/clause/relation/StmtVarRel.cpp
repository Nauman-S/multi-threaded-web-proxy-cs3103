#include "StmtVarRel.h"

#include <memory>
#include <string>
#include <vector>

#include "../../DataRetriever.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


std::string StmtVarRel::LhsValue() {
    return lhs_ref_->GetName();
}

std::string StmtVarRel::RhsValue() {
    return rhs_ref_->GetName();
}

RefType StmtVarRel::LhsRefType() {
    return lhs_ref_->GetRefType();
}

RefType StmtVarRel::RhsRefType() {
    return rhs_ref_->GetRefType();
}


std::pair<ValType, ValType> StmtVarRel::ValTypes() {
    return std::pair<ValType, ValType>(lhs_ref_->GetValType(), rhs_ref_->GetValType());
}

std::optional<int> StmtVarRel::LhsValueAsInt() {
    return lhs_ref_->ValueAsInt();
}

std::shared_ptr<ResWrapper> StmtVarRel::GetMatch(DataRetriever& retriever) {
    return retriever.retrieve(*this);
}

int StmtVarRel::CountSynonyms() {
    vector<shared_ptr<Ref>> args = { lhs_ref_, rhs_ref_ };
    return Clause::CountSynonyms(args);
}

std::shared_ptr<std::vector<std::string>> StmtVarRel::GetSynonyms() {
    vector<shared_ptr<Ref>> args = { lhs_ref_, rhs_ref_ };
    return Clause::GetSynonyms(args);
}
