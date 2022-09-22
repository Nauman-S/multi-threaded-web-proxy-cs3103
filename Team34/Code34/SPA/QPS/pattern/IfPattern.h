#pragma once

#include <memory>
#include <string>

#include "../reference/Ref.h"
#include "../reference/IfRef.h"
#include "../reference/VarRef.h"
#include "../reference/ValType.h"
#include "Pattern.h"
#include "PatternType.h"


class IfPattern
	: public Pattern
{
protected:
	std::shared_ptr<IfRef> if_ref_;
	std::shared_ptr<VarRef> var_ref_;
	std::shared_ptr<Ref> if_block_wildcard_{ nullptr };
	std::shared_ptr<Ref> else_block_wildcard_{ nullptr };

public:
	IfPattern(std::shared_ptr<IfRef> if_ref, std::shared_ptr<VarRef> var_ref)
		: if_ref_{ if_ref }, var_ref_{ var_ref } {};

	std::string StmtSyn() override { return if_ref_->GetName(); }

	RefType StmtRefType() override { return RefType::kIfRef; }

	ValType StmtValType() override { return if_ref_->GetValType(); }

	std::string VarName() override { return var_ref_->GetName(); }

	ValType VarValType() override { return var_ref_->GetValType(); }

	PatternType GetPatternType() override { return PatternType::kIfPattern; }
};