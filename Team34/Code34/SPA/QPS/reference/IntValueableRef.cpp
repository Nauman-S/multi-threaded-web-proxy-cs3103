#include "IntValueableRef.h"
#include "ValType.h"

bool IntValueableRef::IsIntValued() {
	return val_type_ == ValType::kLineNum;
}

std::optional<int> IntValueableRef::ValueAsInt() {
	if (IsIntValued()) {
		return std::optional<int>(std::stoi(val_));
	}
	else {
		return std::optional<int>();
	}
}