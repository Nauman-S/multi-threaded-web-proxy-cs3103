#include "With.h"

#include "../DataRetriever.h"

std::shared_ptr<ResWrapper> With::GetMatch(DataRetriever& retriever)
{
	return retriever.retrieve(*this);
}

int With::CountSynonyms()
{
    int res = 0;
    if (lhs_ref_ptr_->GetValType() == ValType::kSynonym) {
        res += 1;
    }
    if (rhs_ref_ptr_->GetValType() == ValType::kSynonym) {
        res += 1;
    }

    return res;
}
