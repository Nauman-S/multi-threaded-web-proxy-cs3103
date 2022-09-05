#include "UsesManager.h"

bool UsesManager::CheckUses(StmtNum stmt_num, Variable var)
{
	return uses_sv_store_.CheckRelation(stmt_num, var);
}

bool UsesManager::CheckUses(Procedure proc_name, Variable var)
{
	return uses_pv_store_.CheckRelation(proc_name, var);
}

void UsesManager::SetUses(StmtNum stmt_num, Variable var)
{
	uses_sv_store_.SetRelation(stmt_num, var);
}
void UsesManager::SetUses(Procedure proc_name, Variable var)
{
	uses_pv_store_.SetRelation(proc_name, var);
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> UsesManager::GetAllSVUses()
{
	return uses_sv_store_.GetAllRelations();
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> UsesManager::GetAllPVUses()
{
	return uses_pv_store_.GetAllRelations();
}

std::shared_ptr <std::unordered_set<Variable>> UsesManager::GetVarByStmtNum(StmtNum stmt_num)
{
	return uses_sv_store_.GetTByS(stmt_num);
}

std::shared_ptr <std::unordered_set<Variable>> UsesManager::GetVarByProcName(Procedure proc_name)
{
	return uses_pv_store_.GetTByS(proc_name);
}

std::shared_ptr <std::unordered_set<StmtNum>> UsesManager::GetStmtNumByVar(Variable var)
{
	return uses_sv_store_.GetSByT(var);
}

std::shared_ptr <std::unordered_set<Procedure>> UsesManager::GetProcNameByVar(Variable var)
{
	return uses_pv_store_.GetSByT(var);
}