#include "PatternManager.h"

void PatternManager::AddAssignPattern(StmtNum stmt_num, Variable var, std::string expr)
{
	assert(assign_statement_map_.find(stmt_num) == assign_statement_map_.end());
	assign_statement_map_[stmt_num] = std::make_pair(var, expr);
}

bool PatternManager::IsAssignPatternExactMatch(StmtNum stmt_num, Variable var, std::string expr)
{
	return IsAssignPatternVarExprHelper(stmt_num, var, expr, true);
}

bool PatternManager::IsAssignPatternExactMatch(StmtNum stmt_num, std::string expr)
{
	return IsAssignPatternExprHelper(stmt_num, expr, true);
}

bool PatternManager::IsAssignPatternPartialMatch(StmtNum stmt_num, Variable var, std::string expr)
{
	return IsAssignPatternVarExprHelper(stmt_num, var, expr, false);
}

bool PatternManager::IsAssignPatternPartialMatch(StmtNum stmt_num, std::string expr)
{
	return IsAssignPatternExprHelper(stmt_num, expr, false);
}

bool PatternManager::IsAssignPatternExprHelper(StmtNum stmt_num, std::string expr, bool isExactMatch)
{
	auto iter = assign_statement_map_.find(stmt_num);
	if (iter != assign_statement_map_.end())
	{
		std::pair<Variable, std::string> pair = assign_statement_map_[stmt_num];
		std::string stored_expr = pair.second;
		if (isExactMatch && expr == stored_expr)
		{
			return true;
		}
		if (!isExactMatch && stored_expr.find(expr) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

bool PatternManager::IsAssignPatternVarExprHelper(StmtNum stmt_num, Variable var, std::string expr, bool isExactMatch)
{
	auto iter = assign_statement_map_.find(stmt_num);
	if (iter != assign_statement_map_.end())
	{
		std::pair<Variable, std::string> pair = assign_statement_map_[stmt_num];
		Variable stored_var = pair.first;
		std::string stored_expr = pair.second;
		if (isExactMatch && var == stored_var && expr == stored_expr)
		{
			return true;
		}
		if (!isExactMatch && var == stored_var && stored_expr.find(expr) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}
