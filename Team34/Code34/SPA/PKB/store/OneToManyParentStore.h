#pragma once

#include "OneToManyTransitiveRelationStore.h"

template <typename T>
class OneToManyParentStore : public OneToManyTransitiveRelationStore<T>
{
public:
	void SetTransitiveRelation(T left, T right);
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations();
private:
	std::vector<std::pair<T, T>> all_transitive_relations_;
};

template<typename T>
inline void OneToManyParentStore<T>::SetTransitiveRelation(T left, T right)
{
	std::pair<T, T> pair = std::make_pair(left, right);
	if (std::find(all_transitive_relations_.begin(), all_transitive_relations_.end(), pair) == all_transitive_relations_.end())
	{
		all_transitive_relations_.push_back(pair);
	}
}

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> OneToManyParentStore<T>::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<T, T>>>(all_transitive_relations_);
}
