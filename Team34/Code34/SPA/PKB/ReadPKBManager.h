#pragma once
#include <vector>
#include <unordered_set>
#include <memory>

#include "manager/ModifiesManager.h"
#include "manager/UsesManager.h"

class ReadPKBManager
{
public:
	static std::unique_ptr<ReadPKBManager> GetInstance()
	{
		std::unique_ptr<ReadPKBManager> manager(new ReadPKBManager());
		return manager;
	}

	// APIs related to Uses relation
	bool CheckUses(int stmt_num, std::string var);
	bool CheckUses(std::string proc_name, std::string var);
	const std::vector<std::pair<int, std::string>>& GetAllSVUses();
	const std::vector<std::pair<std::string, std::string>>& GetAllPVUses();
	std::unordered_set<std::string> GetUsesVarByStmtNum(int stmt_num);
	std::unordered_set<std::string> GetUsesVarByProcName(std::string proc_name);
	std::unordered_set<int> GetUsesStmtNumByVar(std::string var);
	std::unordered_set<std::string> GetUsesProcNameByVar(std::string var);
	
	// APIs related to Modifies relation
	bool CheckModifies(int stmt_num, std::string var);
	bool CheckModifies(std::string proc_name, std::string var);
	const std::vector<std::pair<int, std::string>>& GetAllSVModifies();
	const std::vector<std::pair<std::string, std::string>>& GetAllPVModifies();
	std::unordered_set<std::string> GetModifiesVarByStmtNum(int stmt_num);
	std::unordered_set<std::string> GetModifiesVarByProcName(std::string proc_name);
	std::unordered_set<int> GetModifiesStmtNumByVar(std::string var);
	std::unordered_set<std::string> GetModifiesProcNameByVar(std::string var);
private:
	ModifiesManager modifies_manager_;
	UsesManager uses_manager_;
};