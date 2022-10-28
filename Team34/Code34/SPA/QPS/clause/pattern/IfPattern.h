#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Pattern.h"
#include "../ClauseType.h"
#include "../../reference/Ref.h"
#include "../../reference/IfRef.h"
#include "../../reference/VarRef.h"
#include "../../reference/ValType.h"
#include "../../optimization/PriorityManager.h"


class IfPattern : public Pattern {
protected:
    std::shared_ptr<IfRef> if_ref_;
    std::shared_ptr<VarRef> var_ref_;
    std::shared_ptr<Ref> if_block_wildcard_{ nullptr };
    std::shared_ptr<Ref> else_block_wildcard_{ nullptr };

public:
    IfPattern(std::shared_ptr<IfRef> if_ref, std::shared_ptr<VarRef> var_ref)
        : if_ref_{ if_ref }, var_ref_{ var_ref } {
    };

    std::string StmtSyn() override { return if_ref_->GetName(); }

    RefType StmtRefType() override { return RefType::kIfRef; }

    ValType StmtValType() override { return if_ref_->GetValType(); }

    std::string VarName() override { return var_ref_->GetName(); }

    ValType VarValType() override { return var_ref_->GetValType(); }

    ClauseType GetPatternType() override { return ClauseType::kIfPattern; }

    std::shared_ptr<ExprSpec> GetExprSpec() override { return nullptr; }

    int CountSynonyms() override;

    Priority GetPriority(PriorityManager& pm) override;

    std::shared_ptr<std::vector<std::string>> GetSynonyms() override;
};