#pragma once
#include <unordered_map>
#include <unordered_set>

#template <class T>
class PVRelationStore
{
private:
	std::unordered_map<std::string, std::unordered_set<std::string>> procToVarMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> varToProcMap;
};