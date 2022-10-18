#include "FollowsRelationStore.h"

void FollowsRelationStore::SetTransitiveRelation(StmtNum left, StmtNum right) {
	all_transitive_relations_.push_back(std::make_pair(left, right));
}


std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> FollowsRelationStore::GetAllTransitiveRelations() {
	return std::make_shared<std::vector<std::pair<StmtNum, StmtNum>>>(all_transitive_relations_);
}

void FollowsRelationStore::Clear() {
	OneToOneRelationStore::Clear();
	all_transitive_relations_.clear();
}
