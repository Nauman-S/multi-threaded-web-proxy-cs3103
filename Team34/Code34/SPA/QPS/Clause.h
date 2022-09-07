#pragma once

#include <memory>

#include "query_result/ResWrapper.h"
#include "DataRetriever.h"

class Clause
{
public:
	virtual std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) = 0;
};

