#include "UsesManager.h"

PVRelationStore uses_pv_store_;
SVRelationStore uses_sv_store_;

bool UsesManager::CheckUses(int stmt_num, std::string var)
{
	return uses_sv_store_.CheckSVRelation(stmt_num, var);
}

bool UsesManager::CheckUses(std::string proc_name, std::string var)
{
	return uses_pv_store_.CheckPVRelation(proc_name, var);
}

void UsesManager::SetUses(int stmt_num, std::string var)
{
	uses_sv_store_.SetSVRelation(stmt_num, var);
}
void UsesManager::SetUses(std::string proc_name, std::string var)
{
	uses_pv_store_.SetPVRelation(proc_name, var);
}

const std::vector<std::pair<int, std::string>>& UsesManager::GetAllSVUses()
{
	return *uses_sv_store_.GetAllSVRelations();
}

const std::vector<std::pair<std::string, std::string>>& UsesManager::GetAllPVUses()
{
	return *uses_pv_store_.GetAllPVRelations();
}

std::unordered_set<std::string> UsesManager::GetVarByStmtNum(int stmt_num)
{
	return uses_sv_store_.GetVarByStmtNum(stmt_num);
}

std::unordered_set<std::string> UsesManager::GetVarByProcName(std::string proc_name)
{
	return uses_pv_store_.GetVarByProc(proc_name);
}

std::unordered_set<int> UsesManager::GetStmtNumByVar(std::string var)
{
	return uses_sv_store_.GetStmtNumByVar(var);
}

std::unordered_set<std::string> UsesManager::GetProcNameByVar(std::string var)
{
	return uses_pv_store_.GetProcByVar(var);
}