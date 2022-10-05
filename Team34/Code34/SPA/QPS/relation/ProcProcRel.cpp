#include "ProcProcRel.h"

#include <string>
#include <memory>

#include "../DataRetriever.h"


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
	int res = 0;
	if (lhs_ref_->GetValType() == ValType::kSynonym) {
		res += 1;
	}
	if (rhs_ref_->GetValType() == ValType::kSynonym) {
		res += 1;
	}
	
	return res;
}
