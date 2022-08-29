#pragma once
#include <unordered_map>
#include <unordered_set>

class PVRelationStore
{
public:
	bool CheckPVRelation(std::string proc_name, std::string var);
	// std::vector<std::pair<std::string, std::string>> GetAllPVRelations();
	void SetPVRelation(std::string proc_name, std::string var);
	std::unordered_set<std::string> GetVariableByProcedureName(std::string proc_name);
	std::unordered_set<std::string> GetProcedureNameByVariable(std::string var);
private:
	std::unordered_map<std::string, std::unordered_set<std::string>> proc_name_to_var_map_;
	std::unordered_map<std::string, std::unordered_set<std::string>> var_to_proc_name_map_;
};