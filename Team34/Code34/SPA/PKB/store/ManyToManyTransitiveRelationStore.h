#pragma once

#include <queue>
#include <unordered_set>

#include "ManyToManyRelationStore.h"

template <typename T>
class ManyToManyTransitiveRelationStore : public ManyToManyRelationStore<T, T>
{
public:
	bool CheckTransitiveRelation(T left, T right);
	std::shared_ptr<std::unordered_set<T>> GetAllTransitiveRHS(T t);
	std::shared_ptr<std::unordered_set<T>> GetAllTransitiveLHS(T t);
	virtual std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations() = 0;
};

template<typename T>
inline bool ManyToManyTransitiveRelationStore<T>::CheckTransitiveRelation(T left, T right)
{
	std::unordered_set<T> visited;
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
			if (visited.find(*iter) != visited.end())
			{
				continue;
			}
			if (*iter == right)
			{
				return true;
			}
			else
			{
				visited.insert(*iter);
				queue.push(*iter);
			}
		}
	}
	return false;
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> ManyToManyTransitiveRelationStore<T>::GetAllTransitiveRHS(T t)
{
	return GetAllElements(t, s_to_t_map_);
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> ManyToManyTransitiveRelationStore<T>::GetAllTransitiveLHS(T t)
{
	return GetAllElements(t, t_to_s_map_);
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> GetAllElements(T t, std::unordered_map<T, std::unordered_set<T>>& map)
{
	std::shared_ptr<std::unordered_set<T>> all_elements = std::make_shared<std::unordered_set<T>>();
	std::unordered_set<T> visited;
	std::queue<T> queue;
	queue.push(t);
	while (!queue.empty())
	{
		T ptr = queue.front();
		queue.pop();
		auto iter = map.find(ptr);
		if (iter == map.end())
		{
			continue;
		}
		std::unordered_set<T>& elements = map[ptr];
		for (auto iter = elements.begin(); iter != elements.end(); ++iter)
		{
			if (visited.find(*iter) != visited.end())
			{
				continue;
			}
			all_elements->insert(*iter);
			visited.insert(*iter);
			queue.push(*iter);
		}
	}
	return all_elements;
}