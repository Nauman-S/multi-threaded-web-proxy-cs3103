#pragma once
#include<vector>

#include <.\store\PVRelationStore.h>
#include <.\store\SVRelationStore.h>

class ModifiesManager
{
public:
	bool CheckModifies(int stmt_num, std::string var);
	bool CheckModifies(std::string proc_name, std::string var);
	void SetModifies(int stmt_num, std::string var);
	void SetModifies(std::string proc_name, std::string var);
	std::vector<std::pair<int, std::string>> GetAllSVModifies();
	std::vector<std::pair<std::string, std::string>> GetAllPVModifies();
	std::vector<std::string> GetVarByStmtNum(int stmt_num);
	std::vector<std::string> GetVarByProcName(std::string proc_name);
	std::vector<int> GetStmtNumByVar(std::string var);
	std::vector<std::string> GetProcNameByVar(std::string var);
private:
	PVRelationStore modifies_sv_store_;
	SVRelationStore modifies_sv_store_;
};