#pragma once

#include <memory>

#include "ClauseType.h"
#include "PriorityManager.h"
#include "query_result/ResWrapper.h"
#include "../Utils/type/TypeDef.h"
//#include "DataRetriever.h"
class DataRetriever;


class Clause
{
public:

	virtual std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) = 0;

	virtual int CountSynonyms() = 0;

	virtual Priority GetPriority(PriorityManager pm) = 0;
};

