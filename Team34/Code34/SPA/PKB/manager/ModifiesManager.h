#pragma once
#include <vector>
#include <unordered_set>

#include "../store/PVRelationStore.h"
#include "../store/SVRelationStore.h"

class ModifiesManager
{
public:
	bool CheckModifies(int stmt_num, std::string var);
	bool CheckModifies(std::string proc_name, std::string var);
	void SetModifies(int stmt_num, std::string var);
	void SetModifies(std::string proc_name, std::string var);
	std::vector<std::pair<int, std::string>> GetAllSVModifies();
	std::vector<std::pair<std::string, std::string>> GetAllPVModifies();
	std::unordered_set<std::string> GetVarByStmtNum(int stmt_num);
	std::unordered_set<std::string> GetVarByProcName(std::string proc_name);
	std::unordered_set<int> GetStmtNumByVar(std::string var);
	std::unordered_set<std::string> GetProcNameByVar(std::string var);
private:
	PVRelationStore modifies_pv_store_;
	SVRelationStore modifies_sv_store_;
};