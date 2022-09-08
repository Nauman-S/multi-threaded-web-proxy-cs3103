#pragma once

#include "IntValueableRef.h"
#include "../../Utils/type/RefType.h"

class ConstRef 
	: public IntValueableRef
{
	using IntValueableRef::IntValueableRef;

public:
	const RefType GetRefType() override { return RefType::kConstRef; }
};

