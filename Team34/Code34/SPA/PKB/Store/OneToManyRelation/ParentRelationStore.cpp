#include "ParentRelationStore.h"

void ParentRelationStore::SetTransitiveRelation(StmtNum left, StmtNum right)
{
	std::pair<StmtNum, StmtNum> pair = std::make_pair(left, right);
	if (std::find(all_transitive_relations_.begin(), all_transitive_relations_.end(), pair) == all_transitive_relations_.end())
	{
		all_transitive_relations_.push_back(pair);
	}
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ParentRelationStore::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<StmtNum, StmtNum>>>(all_transitive_relations_);
}

void ParentRelationStore::Clear()
{
	OneToManyRelationStore::Clear();
	all_transitive_relations_.clear();
}
