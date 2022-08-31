#pragma once
#include <string>


class Rel
{
public:
	virtual std::string LhsValue()=0;
	virtual std::string RhsValue()=0;
};

