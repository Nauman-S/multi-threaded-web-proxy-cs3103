#pragma once

#include "OneToOneTransitiveRelationStore.h"

template <typename T>
class FollowsRelationStore : public OneToOneTransitiveRelationStore<T>
{
public:
	void SetTransitiveRelation(T left, T right);
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations();
private:
	std::vector<std::pair<T, T>> all_transitive_relations_;
};

template<typename T>
inline void FollowsRelationStore<T>::SetTransitiveRelation(T left, T right)
{
	all_transitive_relations_.push_back(std::make_pair(left, right));
}

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> FollowsRelationStore<T>::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<T, T>>>(all_transitive_relations_);
}
