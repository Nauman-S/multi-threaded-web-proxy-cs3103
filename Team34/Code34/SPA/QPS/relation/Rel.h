#pragma once

#include <string>

#include "../Clause.h"
#include "../reference/ValType.h"

class Rel:
	public Clause
{
public:
	virtual std::string LhsValue()=0;

	virtual std::string RhsValue()=0;

	virtual std::pair<ValType, ValType> ValTypes() = 0;
};

