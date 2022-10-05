#pragma once

#include <memory>
#include <string>

#include "Pattern.h"
#include "../ClauseType.h"
#include "../reference/AssignRef.h"
#include "../reference/VarRef.h"
#include "../reference/ValType.h"
#include "../../Utils/expression/ExprSpec.h"



class AssignPattern
	: public Pattern
{
protected:
	std::shared_ptr<AssignRef> assign_ref_;
	std::shared_ptr<VarRef> var_ref_;
	std::shared_ptr<ExprSpec> expr_spec_;

public:
	AssignPattern(std::shared_ptr<AssignRef> a, std::shared_ptr<VarRef> lhs, std::shared_ptr <ExprSpec> rhs) 
		: assign_ref_{ a }, var_ref_{ lhs }, expr_spec_{ rhs } {};

	std::string StmtSyn() override { return assign_ref_->GetName(); }

	RefType StmtRefType() override { return RefType::kAssignRef; }

	ValType StmtValType() override { return assign_ref_->GetValType(); }

	std::string VarName() override { return var_ref_->GetName(); }

	ValType VarValType() override { return var_ref_->GetValType(); }

	ClauseType GetPatternType() override { return ClauseType::kAssignPattern; }

	std::shared_ptr<ExprSpec> GetExprSpec() override { return expr_spec_; }

	int CountSynonyms() override;

	Priority GetPriority(PriorityManager pm) override;

};

