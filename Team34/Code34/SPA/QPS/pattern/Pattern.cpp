#include "Pattern.h"

#include <memory>

#include "../DataRetriever.h"

std::shared_ptr<ResWrapper> Pattern::GetMatch(DataRetriever& retriever)
{
	{ return retriever.retrieve(*this); }
}
