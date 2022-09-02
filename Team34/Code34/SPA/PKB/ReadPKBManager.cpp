#include "ReadPKBManager.h"

// APIs related to Variable entity
bool ReadPKBManager::IsVariable(std::string var)
{
    return variable_manager_.IsVariable(var);
}

std::shared_ptr<unordered_set<int>> ReadPKBManager::GetAllConstants()
{
    return
}

// APIs related to Constant entity
bool ReadPKBManager::IsConstant(int constant)
{
    return constant_manager_.IsConstant(constant);
}

// APIs related to Uses relation
bool ReadPKBManager::CheckUses(int stmt_num, std::string var)
{
	return uses_manager_.CheckUses(stmt_num, var);
}

bool ReadPKBManager::CheckUses(std::string proc_name, std::string var)
{
	return uses_manager_.CheckUses(proc_name, var);
}

const std::vector<std::pair<int, std::string>>& ReadPKBManager::GetAllSVUses()
{
	return uses_manager_.GetAllSVUses();
}

const std::vector<std::pair<std::string, std::string>>& ReadPKBManager::GetAllPVUses()
{
	return uses_manager_.GetAllPVUses();
}

std::unordered_set<std::string> ReadPKBManager::GetUsesVarByStmtNum(int stmt_num)
{
	return uses_manager_.GetVarByStmtNum(stmt_num);
}

std::unordered_set<std::string> ReadPKBManager::GetUsesVarByProcName(std::string proc_name)
{
	return uses_manager_.GetVarByProcName(proc_name);
}

std::unordered_set<int> ReadPKBManager::GetUsesStmtNumByVar(std::string var)
{
	return uses_manager_.GetStmtNumByVar(var);
}

std::unordered_set<std::string> ReadPKBManager::GetUsesProcNameByVar(std::string var)
{
	return uses_manager_.GetProcNameByVar(var);
}


// APIs related to Modifies relation
bool ReadPKBManager::CheckModifies(int stmt_num, std::string var)
{
	return modifies_manager_.CheckModifies(stmt_num, var);
}

bool ReadPKBManager::CheckModifies(std::string proc_name, std::string var)
{
	return modifies_manager_.CheckModifies(proc_name, var);
}

const std::vector<std::pair<int, std::string>>& ReadPKBManager::GetAllSVModifies()
{
	return modifies_manager_.GetAllSVModifies();
}

const std::vector<std::pair<std::string, std::string>>& ReadPKBManager::GetAllPVModifies()
{
	return modifies_manager_.GetAllPVModifies();
}

std::unordered_set<std::string> ReadPKBManager::GetModifiesVarByStmtNum(int stmt_num)
{
	return modifies_manager_.GetVarByStmtNum(stmt_num);
}

std::unordered_set<std::string> ReadPKBManager::GetModifiesVarByProcName(std::string proc_name)
{
	return modifies_manager_.GetVarByProcName(proc_name);
}

std::unordered_set<int> ReadPKBManager::GetModifiesStmtNumByVar(std::string var)
{
	return modifies_manager_.GetStmtNumByVar(var);
}

std::unordered_set<std::string> ReadPKBManager::GetModifiesProcNameByVar(std::string var)
{
	return modifies_manager_.GetProcNameByVar(var);
}