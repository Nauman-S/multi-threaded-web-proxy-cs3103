#include "PatternManager.h"

void PatternManager::AddAssignPattern(StmtNum stmt_num, Variable var, std::string expr)
{
	assert(assign_statement_map_.find(stmt_num) == assign_statement_map_.end());
	assign_statement_map_[stmt_num] = std::make_pair(var, expr);
}

bool PatternManager::IsAssignPatternMatch(StmtNum stmt_num, std::string expr, bool is_exact_match)
{
	auto iter = assign_statement_map_.find(stmt_num);
	if (iter != assign_statement_map_.end())
	{
		std::pair<Variable, std::string> pair = assign_statement_map_[stmt_num];
		std::string stored_expr = pair.second;
		if (is_exact_match && expr == stored_expr)
		{
			return true;
		}
		if (!is_exact_match && stored_expr.find(expr) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

bool PatternManager::IsAssignPatternMatch(StmtNum stmt_num, Variable var, std::string expr, bool is_exact_match)
{
	auto iter = assign_statement_map_.find(stmt_num);
	if (iter != assign_statement_map_.end())
	{
		std::pair<Variable, std::string> pair = assign_statement_map_[stmt_num];
		Variable stored_var = pair.first;
		std::string stored_expr = pair.second;
		if (is_exact_match && var == stored_var && expr == stored_expr)
		{
			return true;
		}
		if (!is_exact_match && var == stored_var && stored_expr.find(expr) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> PatternManager::GetAssignPatternMatch(std::string expr, bool is_exact_match)
{
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> all_sv_pairs = std::make_shared<std::vector<std::pair<StmtNum, Variable>>>();
	for (auto iter = assign_statement_map_.begin(); iter != assign_statement_map_.end(); ++iter)
	{
		StmtNum stmt_num = iter->first;
		std::pair<Variable, std::string> pair = iter->second;
		if (is_exact_match && expr == pair.second)
		{
			all_sv_pairs->push_back(std::make_pair(stmt_num, pair.first));
		}
		if (!is_exact_match && pair.second.find(expr) != std::string::npos)
		{
			all_sv_pairs->push_back(std::make_pair(stmt_num, pair.first));
		}
	}
	return all_sv_pairs;
}
