#pragma once

#include "OneToOneRelationStore.h"

template <typename T>
class OneToOneTransitiveRelationStore : public OneToOneRelationStore<T, T>
{
public:
	// Transitive Relation methods
	bool CheckTransistiveRelation(T left, T right);
	void SetTransitiveRelation(T left, T right);
	std::shared_ptr<std::unordered_set<T>> GetAllRHSByLHS(T left);
	std::shared_ptr<std::unordered_set<T>> GetAllLHSByRHS(T right);
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations();
private:
	std::vector<std::pair<T, T>> all_transitive_relations_;
};

template <typename T>
inline bool OneToOneTransitiveRelationStore<T>::CheckTransistiveRelation(T left, T right)
{
	auto iter = left_to_right_map_.find(left);
	T next = left;
	while (iter != left_to_right_map_.end())
	{
		next = left_to_right_map_[next];
		if (next == right)
		{
			return true;
		}
		iter = left_to_right_map_.find(next);
	}
	return false;
}

template <typename T>
inline void OneToOneTransitiveRelationStore<T>::SetTransitiveRelation(T left, T right)
{
	all_transitive_relations_.push_back(std::make_pair(left, right));
}

template <typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToOneTransitiveRelationStore<T>::GetAllRHSByLHS(T left)
{
	return GetAllHelper(left, left_to_right_map_);
}

template <typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToOneTransitiveRelationStore<T>::GetAllLHSByRHS(T right)
{
	return GetAllHelper(right, right_to_left_map_);
}

template <typename T>
inline std::shared_ptr<std::unordered_set<T>> GetAllHelper(T start, std::unordered_map<T, T>& map)
{
	std::shared_ptr<std::unordered_set<T>> all = std::make_shared<std::unordered_set<T>>();
	auto iter = map.find(start);
	T next = start;
	while (iter != map.end())
	{
		next = map[next];
		all->insert(next);
		iter = map.find(next);
	}
	return all;
}

template <typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> OneToOneTransitiveRelationStore<T>::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<T, T>>>(all_transitive_relations_);
}
