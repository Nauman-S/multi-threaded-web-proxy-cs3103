#include "With.h"

#include "../DataRetriever.h"

std::shared_ptr<ResWrapper> With::GetMatch(DataRetriever& retriever)
{
	return retriever.retrieve(*this);
}
