#include "PVRelationStore.h"

std::unordered_map<std::string, std::unordered_set<std::string>> proc_name_to_var_map_;
std::unordered_map<std::string, std::unordered_set<std::string>> var_to_proc_name_map_;

bool PVRelationStore::CheckPVRelation(std::string proc_name, std::string var)
{
	auto iter = var_to_proc_name_map_.find(var);
	if (iter != var_to_proc_name_map_.end())
	{
		// found var name key
		return var_to_proc_name_map_[var].find(proc_name) != var_to_proc_name_map_[var].end();
	}
	return false;
}

std::vector<std::pair<std::string, std::string>> GetAllPVRelations()
{
	std::vector<std::pair<std::string, std::string>> all_pv_relations;
	for (const auto& p : proc_name_to_var_map_)
	{
		for (auto iter = p.second.begin(); iter != p.second.end(); iter++)
		{
			all_pv_relations.push_back(std::make_pair(p.first, *iter));
		}
	}
	return all_pv_relations;
}

void PVRelationStore::SetPVRelation(std::string proc_name, std::string var)
{
	proc_name_to_var_map_[proc_name].insert(var);
	var_to_proc_name_map_[var].insert(proc_name);
}

std::unordered_set<std::string> PVRelationStore::GetVariableByProcedureName(std::string proc_name)
{
	auto iter = proc_name_to_var_map_.find(proc_name);
	if (iter == proc_name_to_var_map_.end())
	{
		return {};
	}
	else
	{
		return proc_name_to_var_map_[proc_name];
	}
}

std::unordered_set<std::string> PVRelationStore::GetProcedureNameByVariable(std::string var)
{
	auto iter = var_to_proc_name_map_.find(var);
	if (iter == var_to_proc_name_map_.end())
	{
		return {};
	}
	else
	{
		return var_to_proc_name_map_[var];
	}
}