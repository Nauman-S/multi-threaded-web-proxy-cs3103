#pragma once

#include <string>
#include <memory>

#include "../Clause.h"
#include "../reference/ValType.h"
#include "RelType.h"
#include "../../Utils/type/RefType.h"
#include "../query_result/ResWrapper.h"
class DataRetriever;

class Rel:
	public Clause
{
public:
	virtual std::string LhsValue() = 0;

	virtual std::string RhsValue() = 0;

	virtual RelType GetRelType() = 0;

	virtual RefType LhsRefType() = 0;

	virtual RefType RhsRefType() = 0;

	virtual std::pair<ValType, ValType> ValTypes() = 0;

	virtual std::shared_ptr<ResWrapper> GetMatch(DataRetriever&) = 0;

};

