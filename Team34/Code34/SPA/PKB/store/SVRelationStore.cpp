#include "SVRelationStore.h"

std::unordered_map<int, std::unordered_set<std::string>> stmt_no_to_var_map_;
std::unordered_map<std::string, std::unordered_set<int>> var_to_stmt_no_map_;

bool SVRelationStore::CheckSVRelation(int stmt_no, std::string var)
{
	auto iter = stmt_no_to_var_map_.find(stmt_no);
	if (iter != stmt_no_to_var_map_.end())
	{
		// found stmt_no key
		return stmt_no_to_var_map_[stmt_no].find(var) != stmt_no_to_var_map_[stmt_no].end();
	}
	return false;
}

std::vector<std::pair<int, std::string>> GetAllSVRelations()
{
	std::vector<std::pair<int, std::string>> all_sv_relations;
	for (const auto& p : stmt_no_to_var_map_)
	{
		for (auto iter = p.second.begin(); iter != p.second.end(); iter++)
		{
			all_sv_relations.push_back(std::make_pair(p.first, *iter));
		}
	}
	return all_sv_relations;
}

void SVRelationStore::SetSVRelation(int stmt_no, std::string var)
{
	stmt_no_to_var_map_[stmt_no].insert(var);
	var_to_stmt_no_map_[var].insert(stmt_no);
}

std::unordered_set<std::string> SVRelationStore::GetVariableByStatementNo(int stmt_no)
{
	auto iter = stmt_no_to_var_map_.find(stmt_no);
	if (iter == stmt_no_to_var_map_.end())
	{
		return {};
	}
	else
	{
		return stmt_no_to_var_map_[stmt_no];
	}
}

std::unordered_set<int> SVRelationStore::GetStatementNoByVariable(std::string var)
{
	auto iter = var_to_stmt_no_map_.find(var);
	if (iter == var_to_stmt_no_map_.end())
	{
		return {};
	}
	else
	{
		return var_to_stmt_no_map_[var];
	}
}