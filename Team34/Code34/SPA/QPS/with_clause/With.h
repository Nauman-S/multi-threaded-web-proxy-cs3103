#pragma once

#include <string>
#include <memory>

#include "../Clause.h"
#include "../reference/Ref.h"
#include "../../Utils/type/RefType.h" 
#include "../query_result/ResWrapper.h"
class DataRetriever;

class With
	:public Clause
{
protected:
	std::shared_ptr<Ref> ref_ptr_;  // a synonym reference
	std::string req_val_;  // required value

public:
	With(std::shared_ptr<Ref> ref, std::string val)
		: ref_ptr_{ ref }, req_val_{ val } {};

	RefType RefType() { return ref_ptr_->GetRefType(); }

	std::string RefName() { return ref_ptr_->GetName(); }

	std::string RequiredValue() { return req_val_; }

	std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;

};