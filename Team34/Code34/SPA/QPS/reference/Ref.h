#pragma once

#include <string>

#include "ValType.h"
#include "../../Utils/type/RefType.h"

class Ref
{
protected:
	ValType val_type_;
	std::string val_;

public:
	Ref(ValType type, std::string val)
		:val_type_{ type }, val_{ val } {};

	virtual const std::string& GetName() const { return val_; }

	virtual const ValType GetValType() { return val_type_; }

	virtual const RefType GetRefType() = 0;
};

