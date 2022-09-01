#include "WritePKBManager.h"

// APIs related to Uses relation
void WritePKBManager::SetUses(int stmt_num, std::string var)
{
	uses_manager_.SetUses(stmt_num, var);
}

void WritePKBManager::SetUses(std::string proc_name, std::string var)
{
	uses_manager_.SetUses(proc_name, var);
}

//APIs related to Modifies relation
void WritePKBManager::SetModifies(int stmt_num, std::string var)
{
	modifies_manager_.SetModifies(stmt_num, var);
}

void WritePKBManager::SetModifies(std::string proc_name, std::string var)
{
	modifies_manager_.SetModifies(proc_name, var);
}