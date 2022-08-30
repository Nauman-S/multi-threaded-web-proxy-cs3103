#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

class SVRelationStore
{
public:
	bool CheckSVRelation(int stmt_num, std::string var);
	std::vector<std::pair<int, std::string>>* GetAllSVRelations();
	void SetSVRelation(int stmt_num, std::string var);
	std::unordered_set<std::string> GetVarByStmtNum(int stmt_num);
	std::unordered_set<int> GetStmtNumByVar(std::string var);
private:
	std::unordered_map<int, std::unordered_set<std::string>> stmt_num_to_var_map_;
	std::unordered_map<std::string, std::unordered_set<int>> var_to_stmt_num_map_;
};