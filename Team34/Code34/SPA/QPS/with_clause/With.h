#pragma once

#include <string>
#include <memory>

#include "../Clause.h"
#include "../PriorityManager.h"
#include "../reference/Ref.h"
#include "../reference/ValType.h"
#include "../query_result/ResWrapper.h"
#include "../../Utils/type/TypeDef.h"
#include "../../Utils/type/RefType.h" 
class DataRetriever;


class With
	:public Clause
{
protected:
	// either one of the reference shuold be synonym
	std::shared_ptr<Ref> lhs_ref_ptr_;
	std::shared_ptr<Ref> rhs_ref_ptr_;
	ValType req_lhs_val_type_;
	ValType req_rhs_val_type_;
	bool is_valid_;

public:

	With(std::shared_ptr<Ref> ref1, std::shared_ptr<Ref> ref2)
		: lhs_ref_ptr_{ ref1 }, rhs_ref_ptr_{ ref2 }, is_valid_{ true }, req_lhs_val_type_(ValType::kInt), req_rhs_val_type_{ ValType::kInt } {};

	With(std::shared_ptr<Ref> ref1, std::shared_ptr<Ref> ref2, ValType lhs_type, ValType rhs_type)
		: lhs_ref_ptr_{ ref1 }, rhs_ref_ptr_{ ref2 }, req_lhs_val_type_(lhs_type), req_rhs_val_type_{rhs_type}, is_valid_{ true } {};

	RefType LhsRefType() { return lhs_ref_ptr_->GetRefType(); }

	RefType RhsRefType() { return rhs_ref_ptr_->GetRefType(); }

	std::pair<ValType, ValType> ValTypes() { return std::make_pair(lhs_ref_ptr_->GetValType(), rhs_ref_ptr_->GetValType()); }

	ValType RequiredLhsValType() { return req_lhs_val_type_; }

	ValType RequiredRhsValType() { return req_rhs_val_type_; }

	std::string LhsValue() { return lhs_ref_ptr_->GetName(); }

	std::string RhsValue() { return rhs_ref_ptr_->GetName(); }

	std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;

	int CountSynonyms() override;

	Priority GetPriority(PriorityManager pm) override;
};