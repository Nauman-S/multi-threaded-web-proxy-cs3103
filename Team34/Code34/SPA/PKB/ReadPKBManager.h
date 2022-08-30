#pragma once
#include <vector>

#include "manager/ModifiesManager.h"
#include "manager/UsesManager.h"

class ReadPKBManager
{
public:
	// APIs related to Uses relation
	bool CheckUses(int stmt_num, std::string var);
	bool CheckUses(std::string proc_name, std::string var);
	std::vector<std::pair<int, std::string>> GetAllSVUses();
	std::vector<std::pair<std::string, std::string>> GetAllPVUses();
	std::vector<std::string> GetUsesVarByStmtNum(int stmt_num);
	std::vector<std::string> GetUsesVarByProcName(std::string proc_name);
	std::vector<int> GetUsesStmtNumByVar(std::string);
	std::vector<std::string> GetUsesProcNameByVar(std::string);
	
	// APIs related to Modifies relation
	bool CheckModifies(int stmt_num, std::string var);
	bool CheckModifies(std::string proc_name, std::string var);
	std::vector<std::pair<int, std::string>> GetAllSVModifies();
	std::vector<std::pair<std::string, std::string>> GetAllPVModifies();
	std::vector<std::string> GetModifiesVarByStmtNum(int stmt_num);
	std::vector<std::string> GetModifiesVarByProcName(std::string proc_name);
	std::vector<int> GetModifiesStmtNumByVar(std::string);
	std::vector<std::string> GetModifiesProcNameByVar(std::string);
private:
	ModifiesManager modifies_manager_;
	UsesManager uses_manager_;
};