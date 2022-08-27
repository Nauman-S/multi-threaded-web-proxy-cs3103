#pragma once
#include <unordered_map>
#include <unordered_set>

#template <class T>
class SVRelationStore
{
	private:
		std::unordered_map<int, std::unordered_set<std::string>> stmtToVarMap;
		std::unordered_map<std::string, std::unordered_set<int>> varToStmtMap;
};