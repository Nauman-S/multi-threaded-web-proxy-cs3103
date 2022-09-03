#pragma once

#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "../../Utils/type/RefType.h"

class StatementManager
{
public:
	void AddStatement(int stmt_num, RefType type);
	bool IsStatement(int stmt_num);
	bool IsStatementType(int stmt_num, RefType type);
	const std::unordered_set<int>& GetStatementsByType(RefType type);
	RefType GetTypeByStatement(int stmt_num);

	std::string GetProcedureFromCallStatement(int stmt_num);
	const std::unordered_set<int>& GetCallStatementFromProcedure(std::string proc);
private:
	static std::unordered_map<RefType, std::unordered_set<int>> type_to_stmt_map;
	static std::unordered_map<int,RefType> stmt_to_type_map_;
	static std::unordered_map<int, std::string> call_to_proc_map_;
	static std::unordered_map<std::string, std::unordered_set<int>> proc_to_call_map_;
	
};