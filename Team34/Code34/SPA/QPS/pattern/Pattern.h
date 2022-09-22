#pragma once

#include <string>
#include <optional>
#include <memory>

#include "PatternType.h"
#include "../Clause.h"
#include "../reference/ValType.h"
#include "../../Utils/type/RefType.h"
#include "../../Utils/expression/ExprSpec.h"
class DataRetriever;

class Pattern
	:public Clause
{
	// General structure of Pattern:
	// stmt_syn_ref(var_ref, 2nd arg[, 3rd arg])
public:
	virtual std::string StmtSyn() = 0;

	virtual RefType StmtRefType() = 0;

	virtual ValType StmtValType() = 0;

	virtual std::string VarName() = 0;

	virtual ValType VarValType() = 0;

	virtual PatternType GetPatternType() = 0;

	virtual std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever);  // Implemented in Pattern.cpp

	virtual std::shared_ptr<ExprSpec> GetExprSpec() = 0;
};