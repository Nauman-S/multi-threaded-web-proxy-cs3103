#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../AttrType.h"
#include "../Clause.h"
#include "../../optimization/PriorityManager.h"
#include "../../query_result/ResWrapper.h"
#include "../../reference/Ref.h"
#include "../../reference/ValType.h"
#include "../../../Utils/type/RefType.h"
#include "../../../Utils/type/TypeDef.h"
class DataRetriever;

class With : public Clause {
protected:
    // either one of the reference shuold be synonym
    std::shared_ptr<Ref> lhs_ref_ptr_;
    std::shared_ptr<Ref> rhs_ref_ptr_;
    AttrType lhs_attr_type_;
    AttrType rhs_attr_type_;
    bool is_valid_;

public:
    With(std::shared_ptr<Ref> ref1, std::shared_ptr<Ref> ref2,
        AttrType lhs_attr_type, AttrType rhs_attr_type)
        : lhs_ref_ptr_{ ref1 },
        rhs_ref_ptr_{ ref2 },
        lhs_attr_type_{ lhs_attr_type },
        rhs_attr_type_{ rhs_attr_type },
        is_valid_{ true } {
    };

    RefType LhsRefType() { return lhs_ref_ptr_->GetRefType(); }

    RefType RhsRefType() { return rhs_ref_ptr_->GetRefType(); }

    std::pair<ValType, ValType> ValTypes() {
        return std::make_pair(lhs_ref_ptr_->GetValType(),
            rhs_ref_ptr_->GetValType());
    }

    AttrType LhsAttrType() { return lhs_attr_type_; }

    AttrType RhsAttrType() { return rhs_attr_type_; }

    bool IsLhsAttrTypeDefault() { return lhs_ref_ptr_->GetDefaultAttrType() == lhs_attr_type_; }

    bool IsRhsAttrTypeDefault() { return rhs_ref_ptr_->GetDefaultAttrType() == rhs_attr_type_; }

    std::string LhsValue() { return lhs_ref_ptr_->GetName(); }

    std::string RhsValue() { return rhs_ref_ptr_->GetName(); }

    std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;

    int CountSynonyms() override;

    Priority GetPriority(PriorityManager& pm) override;

    std::shared_ptr<std::vector<std::string>> GetSynonyms() override;
};