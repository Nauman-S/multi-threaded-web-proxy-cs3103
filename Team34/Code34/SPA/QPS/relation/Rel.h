#pragma once
#include <string>
class Relation
{
public:
	virtual std::string LhsValue()=0;
	virtual std::string RhsValue()=0;
};

