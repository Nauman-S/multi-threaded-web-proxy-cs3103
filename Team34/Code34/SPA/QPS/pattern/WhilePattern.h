#pragma once

#include <memory>
#include <string>

#include "../reference/Ref.h"
#include "../reference/WhileRef.h"
#include "../reference/VarRef.h"
#include "../reference/ValType.h"
#include "Pattern.h"
#include "PatternType.h"


class WhilePattern
	: public Pattern
{
protected:
	std::shared_ptr<WhileRef> while_ref_;
	std::shared_ptr<VarRef> var_ref_;
	std::shared_ptr<Ref> while_block_wildcard_{ nullptr };

public:
	WhilePattern(std::shared_ptr<WhileRef> while_ref, std::shared_ptr<VarRef> var_ref)
		: while_ref_{ while_ref }, var_ref_{ var_ref } {};

	std::string StmtSyn() override { return while_ref_->GetName(); }

	RefType StmtRefType() override { return RefType::kWhileRef; }

	ValType StmtValType() override { return while_ref_->GetValType(); }

	std::string VarName() override { return var_ref_->GetName(); }

	ValType VarValType() override { return var_ref_->GetValType(); }

	PatternType GetPatternType() override { return PatternType::kWhilePattern; }

	std::shared_ptr<ExprSpec> GetExprSpec() override { return nullptr; }

	int CountSynonyms() override;
};