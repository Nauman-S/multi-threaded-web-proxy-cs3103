#include "ModifiesManager.h"

bool ModifiesManager::CheckModifies(int stmt_num, std::string var)
{
	return modifies_sv_store_.CheckSVRelation(stmt_num, var);
}

bool ModifiesManager::CheckModifies(std::string proc_name, std::string var)
{
	return modifies_pv_store_.CheckPVRelation(proc_name, var);
}

void ModifiesManager::SetModifies(int stmt_num, std::string var)
{
	modifies_sv_store_.SetSVRelation(stmt_num, var);
}
void ModifiesManager::SetModifies(std::string proc_name, std::string var)
{
	modifies_pv_store_.SetPVRelation(proc_name, var);
}

const std::vector<std::pair<int, std::string>>& ModifiesManager::GetAllSVModifies()
{
	return *modifies_sv_store_.GetAllSVRelations();
}

const std::vector<std::pair<std::string, std::string>>& ModifiesManager::GetAllPVModifies()
{
	return *modifies_pv_store_.GetAllPVRelations();
}

std::unordered_set<std::string> ModifiesManager::GetVarByStmtNum(int stmt_num)
{
	return modifies_sv_store_.GetVarByStmtNum(stmt_num);
}

std::unordered_set<std::string> ModifiesManager::GetVarByProcName(std::string proc_name)
{
	return modifies_pv_store_.GetVarByProc(proc_name);
}

std::unordered_set<int> ModifiesManager::GetStmtNumByVar(std::string var)
{
	return modifies_sv_store_.GetStmtNumByVar(var);
}

std::unordered_set<std::string> ModifiesManager::GetProcNameByVar(std::string var)
{
	return modifies_pv_store_.GetProcByVar(var);
}