#pragma once

#include <memory>
#include <optional>

#include "../reference/AssignRef.h"
#include "../reference/VarRef.h"
#include "../reference/ValType.h"
#include "../../Utils/expression/ExprSpec.h"
#include "../Clause.h"
//#include "../DataRetriever.h"
class DataRetriever;


class Pattern
	: public Clause
{
protected:
	std::shared_ptr<AssignRef> assign_;
	std::shared_ptr<VarRef> lhs_;
	std::shared_ptr <ExprSpec> rhs_;

public:
	Pattern(std::shared_ptr<AssignRef> a, std::shared_ptr<VarRef> lhs, std::shared_ptr <ExprSpec> rhs) : assign_{ a }, lhs_{ lhs }, rhs_{ rhs } {};

	std::string AssignStmtSyn() { return assign_->GetName(); };

	std::optional<int> AssignStmtValueAsInt() { return assign_->ValueAsInt(); };

	std::string LhsValue() { return lhs_->GetName(); };

	ValType AssignStmtValType() { return assign_->GetValType(); };

	ValType LhsValType() { return lhs_->GetValType(); };

	std::shared_ptr<ExprSpec> RhsExprSpec();

	std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;
};

