#pragma once

#include <string>
#include <memory>

#include "../Clause.h"
#include "../reference/Ref.h"
#include "../../Utils/type/RefType.h" 
#include "../reference/ValType.h"
#include "../query_result/ResWrapper.h"
class DataRetriever;

class With
	:public Clause
{
protected:
	// either one of the reference shuold be synonym
	std::shared_ptr<Ref> lhs_ref_ptr_;
	std::shared_ptr<Ref> rhs_ref_ptr_;
	bool is_valid_;

public:
	explicit With(bool is_valid) : lhs_ref_ptr_{ nullptr }, rhs_ref_ptr_{ nullptr }, is_valid_{ is_valid } {};

	With(std::shared_ptr<Ref> ref1, std::shared_ptr<Ref> ref2)
		: lhs_ref_ptr_{ ref1 }, rhs_ref_ptr_{ ref2 }, is_valid_{ true } {};  // Expect LHS always be synonym reference

	RefType RefType() { return lhs_ref_ptr_->GetRefType(); }  // LHS and RHS should be the same RefType

	std::pair<ValType, ValType> ValTypes() { return std::make_pair<ValType, ValType>(lhs_ref_ptr_->GetValType(), rhs_ref_ptr_->GetValType()); }

	std::string LhsValue() { return lhs_ref_ptr_->GetName(); }

	std::string RhsValue() { return rhs_ref_ptr_->GetName(); }

	std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;

};