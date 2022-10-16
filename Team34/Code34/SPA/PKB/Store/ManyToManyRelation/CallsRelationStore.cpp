#include "CallsRelationStore.h"

void CallsRelationStore::SetTransitiveRelation(Procedure left, Procedure right) {
	std::pair<Procedure, Procedure> pair = std::make_pair(left, right);
	if (std::find(all_transitive_relations_.begin(), all_transitive_relations_.end(), pair) == all_transitive_relations_.end()) {
		all_transitive_relations_.push_back(pair);
	}
}

std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> CallsRelationStore::GetAllTransitiveRelations() {
	return std::make_shared<std::vector<std::pair<Procedure, Procedure>>>(all_transitive_relations_);
}

void CallsRelationStore::Clear() {
	ManyToManyTransitiveRelationStore::Clear();
	all_transitive_relations_.clear();
}
