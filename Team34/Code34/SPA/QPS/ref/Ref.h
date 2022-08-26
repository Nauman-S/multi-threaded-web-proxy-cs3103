#pragma once

#include <string>

#include "ValType.h"

class Ref
{
protected:
	ValType val_type_;
	std::string val_;
public:
	explicit Ref(ValType type, std::string val)
		:val_type_{ type }, val_{ val } {};
	virtual const std::string& Value() const { return val_; }
};

