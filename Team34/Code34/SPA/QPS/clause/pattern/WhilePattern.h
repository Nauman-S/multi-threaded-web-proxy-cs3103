#pragma once

#include <memory>
#include <string>

#include "Pattern.h"
#include "../ClauseType.h"
#include "../../reference/Ref.h"
#include "../../reference/WhileRef.h"
#include "../../reference/VarRef.h"
#include "../../reference/ValType.h"
#include "../../PriorityManager.h"


class WhilePattern : public Pattern {
protected:
    std::shared_ptr<WhileRef> while_ref_;
    std::shared_ptr<VarRef> var_ref_;
    std::shared_ptr<Ref> while_block_wildcard_{ nullptr };

public:
    WhilePattern(std::shared_ptr<WhileRef> while_ref, std::shared_ptr<VarRef> var_ref)
        : while_ref_{ while_ref }, var_ref_{ var_ref } {
    };

    std::string StmtSyn() override { return while_ref_->GetName(); }

    RefType StmtRefType() override { return RefType::kWhileRef; }

    ValType StmtValType() override { return while_ref_->GetValType(); }

    std::string VarName() override { return var_ref_->GetName(); }

    ValType VarValType() override { return var_ref_->GetValType(); }

    ClauseType GetPatternType() override { return ClauseType::kWhilePattern; }

    std::shared_ptr<ExprSpec> GetExprSpec() override { return nullptr; }

    int CountSynonyms() override;

    Priority GetPriority(PriorityManager& pm) override;

    std::shared_ptr<std::vector<std::string>> GetSynonyms() override;
};