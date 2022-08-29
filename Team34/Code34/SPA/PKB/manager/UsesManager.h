#pragma once
#include<vector>

#include <.\store\PVRelationStore.h>
#include <.\store\SVRelationStore.h>

class UsesManager
{
public:
	bool CheckUses(int stmt_num, std::string var);
	bool CheckUses(std::string proc_name, std::string var);
	void SetUses(int stmt_num, std::string var);
	void SetUses(std::string proc_name, std::string var);
	std::vector<std::pair<int, std::string>> GetAllSVUses();
	std::vector<std::pair<std::string, std::string>> GetAllPVUses();
	std::vector<std::string> GetVarByStmtNum(int stmt_num);
	std::vector<std::string> GetVarByProcName(std::string proc_name);
	std::vector<int> GetStmtNumByVar(std::string var);
	std::vector<std::string> GetProcNameByVar(std::string var);
private:
	PVRelationStore uses_sv_store_;
	SVRelationStore uses_sv_store_;
};