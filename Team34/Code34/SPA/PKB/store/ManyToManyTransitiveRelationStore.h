#pragma once

#include <queue>

#include "ManyToManyRelationStore.h"

template <typename T>
class ManyToManyTransitiveRelationStore : public ManyToManyRelationStore<T, T>
{
public:
	void SetTransitiveRelation(T left, T right);
	bool CheckTransitiveRelation(T left, T right);
	std::shared_ptr<std::unordered_set<T>> GetAllTransitiveRHS(T t);
	std::shared_ptr<std::unordered_set<T>> GetAllTransitiveLHS(T t);
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations();
private:
	std::vector<std::pair<T, T>> all_transitive_relations_;
};

template<typename T>
inline void ManyToManyTransitiveRelationStore<T>::SetTransitiveRelation(T left, T right)
{
	std::pair<T, T> pair = std::make_pair(left, right);
	if (std::find(all_transitive_relations_.begin(), all_transitive_relations_.end(), pair) == all_transitive_relations_.end())
	{
		all_transitive_relations_.push_back(pair);
	}
}

template<typename T>
inline bool ManyToManyTransitiveRelationStore<T>::CheckTransitiveRelation(T left, T right)
{
	std::queue<T> queue;
	queue.push(left);
	while (!queue.empty())
	{
		T ptr = queue.front();
		queue.pop();
		auto iter = s_to_t_map_.find(ptr);
		if (iter == s_to_t_map_.end())
		{
			continue;
		}
		std::unordered_set<T>& elements = s_to_t_map_[ptr];
		for (auto iter = elements.begin(); iter != elements.end(); ++iter)
		{
			if (*iter == right)
			{
				return true;
			}
			else
			{
				queue.push(*iter);
			}
		}
	}
	return false;
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> ManyToManyTransitiveRelationStore<T>::GetAllTransitiveRHS(T t)
{
	std::shared_ptr<std::unordered_map<T, std::unordered_set<T>>> map = std::make_shared<std::unordered_map<T, std::unordered_set<T>>>(s_to_t_map_);
	return GetAllElements(T t, map);
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> ManyToManyTransitiveRelationStore<T>::GetAllTransitiveLHS(T t)
{
	std::shared_ptr<std::unordered_map<T, std::unordered_set<T>>> map = std::make_shared<std::unordered_map<T, std::unordered_set<T>>>(t_to_s_map_);
	return GetAllElements(T t, map);
}

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> ManyToManyTransitiveRelationStore<T>::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<T, T>>>(all_transitive_relations_);
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> GetAllElements(T t, std::shared_ptr<std::unordered_map<T, std::unordered_set<T>>> map)
{
	std::shared_ptr<std::unordered_set<T>> all_elements = std::make_shared<std::unordered_set<T>>();
	std::queue<T> queue;
	queue.push(t);
	while (!queue.empty())
	{
		T ptr = queue.front();
		queue.pop();
		auto iter = map->find(ptr);
		if (iter == map->end())
		{
			continue;
		}
		std::unordered_set<T>& elements = *map[ptr];
		for (auto iter = elements.begin(); iter != elements.end(); ++iter)
		{
			all_elements->insert(*iter);
			queue.push(*iter);
		}
	}
	return all_elements;
}