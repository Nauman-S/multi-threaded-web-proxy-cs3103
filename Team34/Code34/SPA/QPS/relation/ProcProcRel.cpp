#include "ProcProcRel.h"

#include <memory>
#include <string>
#include <vector>

#include "../DataRetriever.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


std::string ProcProcRel::LhsValue() {
	return lhs_ref_->GetName();
}

std::string ProcProcRel::RhsValue() {
	return rhs_ref_->GetName();
}

RefType ProcProcRel::LhsRefType() {
	return lhs_ref_->GetRefType();
}

RefType ProcProcRel::RhsRefType() {
	return rhs_ref_->GetRefType();
}

std::pair<ValType, ValType> ProcProcRel::ValTypes() {
	return std::make_pair<ValType, ValType>(lhs_ref_->GetValType(), rhs_ref_->GetValType());
}

std::shared_ptr<ResWrapper> ProcProcRel::GetMatch(DataRetriever& retriever) {
	return retriever.retrieve(*this);
}

int ProcProcRel::CountSynonyms()
{
	vector<shared_ptr<Ref>> args = { lhs_ref_, rhs_ref_ };
	return Clause::CountSynonyms(args);
}

std::shared_ptr<std::vector<std::string>> ProcProcRel::GetSynonyms()
{
	vector<shared_ptr<Ref>> args = { lhs_ref_, rhs_ref_ };
	return Clause::GetSynonyms(args);
}
