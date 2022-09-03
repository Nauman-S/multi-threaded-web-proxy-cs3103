#pragma once

#include <string>

#include "../Clause.h"
#include "../reference/ValType.h"
#include "RelType.h"
#include "../query_result/ResWrapper.h"
class DataRetriever;

class Rel:
	public Clause
{
public:
	virtual std::string LhsValue()=0;

	virtual std::string RhsValue()=0;

	virtual std::pair<ValType, ValType> ValTypes() = 0;

	virtual RelType GetRelType() = 0;

	virtual std::unique_ptr<ResWrapper> GetMatch(DataRetriever& data_retriever)=0;
};

