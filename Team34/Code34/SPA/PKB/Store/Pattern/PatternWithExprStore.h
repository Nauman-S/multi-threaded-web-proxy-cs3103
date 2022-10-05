#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>

#include "../../../Utils/type/TypeDef.h"
#include "../../../Utils/expression/ExprSpec.h"
#include "../../../Utils/expression/Expr.h"

class PatternWithExprStore
{
public:
	void AddPattern(StmtNum stmt_num, Expr expr);
	bool IsPatternMatch(StmtNum stmt_num, std::shared_ptr<ExprSpec> expr);
private:
	std::unordered_map<StmtNum, std::shared_ptr<Expr>> statement_map_;
}; 