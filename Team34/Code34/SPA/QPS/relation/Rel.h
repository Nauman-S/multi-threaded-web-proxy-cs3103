#pragma once

#include <string>

#include "../Clause.h"
#include "../reference/ValType.h"
#include "RelType.h"

class Rel:
	public Clause
{
public:
	virtual std::string LhsValue()=0;

	virtual std::string RhsValue()=0;

	virtual std::pair<ValType, ValType> ValTypes() = 0;

	virtual RelType GetRelType() = 0;
};

