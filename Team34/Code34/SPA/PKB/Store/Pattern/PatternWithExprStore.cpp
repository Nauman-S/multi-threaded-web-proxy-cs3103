#include "PatternWithExprStore.h"

void PatternWithExprStore::AddPattern(StmtNum stmt_num, Expr expr)
{
	assert(statement_map_.find(stmt_num) == statement_map_.end());
	statement_map_[stmt_num] = std::make_shared<Expr>(expr);
}

bool PatternWithExprStore::IsPatternMatch(StmtNum stmt_num, std::shared_ptr<ExprSpec> expr)
{
	auto iter = statement_map_.find(stmt_num);
	if (iter != statement_map_.end())
	{
		Expr stored_expr = *statement_map_[stmt_num];
		return expr->IsMatch(stored_expr);
	}
	return false;
}

void PatternWithExprStore::Clear()
{
	statement_map_.clear();
}
