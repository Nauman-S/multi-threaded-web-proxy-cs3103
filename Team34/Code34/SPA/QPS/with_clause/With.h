#pragma once

#include <string>
#include <memory>

#include "../Clause.h"
#include "../reference/Ref.h"
#include "../reference/ValType.h"
#include "../../Utils/type/RefType.h"

class With
	:public Clause
{
protected:
	std::shared_ptr<Ref> ref_ptr_;  // a synonym reference
	ValType req_val_type_;  // required value type
	std::string req_val_;  // required value

public:
	With(std::shared_ptr<Ref> ref, ValType val_type, std::string val)
		: ref_ptr_{ ref }, req_val_type_{ val_type }, req_val_{ val } {};

	RefType RefType() { return ref_ptr_->GetRefType(); }

	std::string RefName() { return ref_ptr_->GetName(); }

	ValType RequiredValType() { return req_val_type_; }

	std::string RequiredValue() { return req_val_; }

};