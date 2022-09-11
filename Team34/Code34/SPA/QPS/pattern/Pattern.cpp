#include "Pattern.h"
#include "../DataRetriever.h"

std::shared_ptr<ExprSpec> Pattern::RhsExprSpec()
{
    return rhs_;
}

std::shared_ptr<ResWrapper> Pattern::GetMatch(DataRetriever& retriever)
{
    return retriever.retrieve(*this);
}
