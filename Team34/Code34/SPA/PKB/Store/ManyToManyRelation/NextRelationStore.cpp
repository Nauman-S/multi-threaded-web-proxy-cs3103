#include "NextRelationStore.h"

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> NextRelationStore::GetAllTransitiveRelations()
{
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations = std::make_shared<std::vector<std::pair<StmtNum, StmtNum>>>();
	for (auto iter = s_to_t_map_.begin(); iter != s_to_t_map_.end(); ++iter)
	{
		StmtNum key = iter->first;
		std::shared_ptr<std::unordered_set<StmtNum>> all_rhs = GetAllTransitiveRHS(key);
		PopulateNextTPairs(all_transitive_relations, key, all_rhs);
	}
	return all_transitive_relations;
}

void NextRelationStore::PopulateNextTPairs(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations,
	StmtNum lhs, std::shared_ptr<std::unordered_set<StmtNum>> all_rhs)
{
	for (auto iter = all_rhs->begin(); iter != all_rhs->end(); ++iter)
	{
		all_transitive_relations->push_back(std::make_pair(lhs, *iter));
	}
}