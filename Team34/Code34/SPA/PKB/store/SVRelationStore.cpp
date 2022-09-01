#include "SVRelationStore.h"

bool SVRelationStore::CheckSVRelation(int stmt_no, std::string var)
{
	auto iter = stmt_num_to_var_map_.find(stmt_no);
	if (iter != stmt_num_to_var_map_.end())
	{
		// found stmt_no key
		return stmt_num_to_var_map_[stmt_no].find(var) != stmt_num_to_var_map_[stmt_no].end();
	}
	return false;
}

std::vector<std::pair<int, std::string>>* SVRelationStore::GetAllSVRelations()
{
	std::vector<std::pair<int, std::string>>* all_sv_relations = new std::vector<std::pair<int, std::string>>();
	for (const auto& p : stmt_num_to_var_map_)
	{
		for (auto iter = p.second.begin(); iter != p.second.end(); iter++)
		{
			all_sv_relations->push_back(std::make_pair(p.first, *iter));
		}
	}
	return all_sv_relations;
}

void SVRelationStore::SetSVRelation(int stmt_no, std::string var)
{
	stmt_num_to_var_map_[stmt_no].insert(var);
	var_to_stmt_num_map_[var].insert(stmt_no);
}

std::unordered_set<std::string> SVRelationStore::GetVarByStmtNum(int stmt_no)
{
	auto iter = stmt_num_to_var_map_.find(stmt_no);
	if (iter == stmt_num_to_var_map_.end())
	{
		return {};
	}
	else
	{
		return stmt_num_to_var_map_[stmt_no];
	}
}

std::unordered_set<int> SVRelationStore::GetStmtNumByVar(std::string var)
{
	auto iter = var_to_stmt_num_map_.find(var);
	if (iter == var_to_stmt_num_map_.end())
	{
		return {};
	}
	else
	{
		return var_to_stmt_num_map_[var];
	}
}