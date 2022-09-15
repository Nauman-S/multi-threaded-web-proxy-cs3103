#include "ModifiesManager.h"

bool ModifiesManager::CheckModifies(StmtNum stmt_num, Variable var)
{
	return modifies_sv_store_.CheckRelation(stmt_num, var);
}

bool ModifiesManager::CheckModifies(Procedure proc_name, Variable var)
{
	return modifies_pv_store_.CheckRelation(proc_name, var);
}

void ModifiesManager::SetModifies(StmtNum stmt_num, Variable var)
{
	modifies_sv_store_.SetRelation(stmt_num, var);
}
void ModifiesManager::SetModifies(Procedure proc_name, Variable var)
{
	modifies_pv_store_.SetRelation(proc_name, var);
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ModifiesManager::GetAllSVModifies()
{
	return modifies_sv_store_.GetAllRelations();
}

std::shared_ptr<std::unordered_set<StmtNum>> ModifiesManager::GetAllStatements()
{
	return modifies_sv_store_.GetAllLHS();
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> ModifiesManager::GetAllPVModifies()
{
	return modifies_pv_store_.GetAllRelations();
}

std::shared_ptr<std::unordered_set<Procedure>> ModifiesManager::GetAllProcedures()
{
	return modifies_pv_store_.GetAllLHS();
}

std::shared_ptr<Variable> ModifiesManager::GetVarByStmtNum(StmtNum stmt_num)
{
	return modifies_sv_store_.GetOne(stmt_num);
}

std::shared_ptr<std::unordered_set<Variable>> ModifiesManager::GetVarByProcName(Procedure proc_name)
{
	return modifies_pv_store_.GetRHSByLHS(proc_name);
}

std::shared_ptr<std::unordered_set<StmtNum>> ModifiesManager::GetStmtNumByVar(Variable var)
{
	return modifies_sv_store_.GetMany(var);
}

std::shared_ptr<std::unordered_set<Procedure>> ModifiesManager::GetProcNameByVar(Variable var)
{
	return modifies_pv_store_.GetLHSByRHS(var);
}