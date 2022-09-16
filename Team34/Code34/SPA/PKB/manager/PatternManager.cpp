#include "PatternManager.h"

void PatternManager::AddAssignPattern(StmtNum stmt_num, Variable var, Expr expr)
{
	assert(assign_statement_map_.find(stmt_num) == assign_statement_map_.end());
	assign_statement_map_[stmt_num] = std::make_pair(var, std::make_shared<Expr>(expr));
}

bool PatternManager::IsAssignPatternMatch(StmtNum stmt_num, std::shared_ptr<ExprSpec> expr)
{
	auto iter = assign_statement_map_.find(stmt_num);
	if (iter != assign_statement_map_.end())
	{
		std::pair<Variable, std::shared_ptr<Expr>> pair = assign_statement_map_[stmt_num];
		Expr stored_expr = *pair.second;
		return expr->IsMatch(stored_expr);
	}
	return false;
}

bool PatternManager::IsAssignPatternMatch(StmtNum stmt_num, Variable var, std::shared_ptr<ExprSpec> expr)
{
	auto iter = assign_statement_map_.find(stmt_num);
	if (iter != assign_statement_map_.end())
	{
		std::pair <Variable, std::shared_ptr<Expr>> pair = assign_statement_map_[stmt_num];
		Variable stored_var = pair.first;
		Expr stored_expr = *pair.second;
		if (var == stored_var)
		{
			return expr->IsMatch(stored_expr);
		}
	}
	return false;
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> PatternManager::GetAssignPatternMatch(std::shared_ptr<ExprSpec> expr)
{
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> all_sv_pairs = std::make_shared<std::vector<std::pair<StmtNum, Variable>>>();
	for (auto iter = assign_statement_map_.begin(); iter != assign_statement_map_.end(); ++iter)
	{
		StmtNum stmt_num = iter->first;
		std::pair<Variable, std::shared_ptr<Expr>> pair = iter->second;
		Variable stored_var = pair.first;
		Expr stored_expr = *pair.second;
		if (expr->IsMatch(stored_expr))
		{
			all_sv_pairs->push_back(std::make_pair(stmt_num, stored_var));
		}
	}
	return all_sv_pairs;
}
