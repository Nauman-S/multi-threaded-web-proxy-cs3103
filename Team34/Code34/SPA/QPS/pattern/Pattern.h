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
	AssignRef& assign_;
	VarRef& lhs_;
	ExprSpec& rhs_;

public:
	Pattern(AssignRef& a, VarRef& lhs, ExprSpec& rhs) : assign_{ a }, lhs_{ lhs }, rhs_{ rhs } {};

	std::string AssignStmtSyn() { return assign_.GetName(); };

	std::optional<int> AssignStmtValueAsInt() { return assign_.ValueAsInt(); };

	std::string LhsValue() { return lhs_.GetName(); };

	ValType AssignStmtValType() { return assign_.GetValType(); };

	ValType LhsValType() { return lhs_.GetValType(); };

	std::shared_ptr<ExprSpec> RhsExprSpec();

	std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) override;
};

