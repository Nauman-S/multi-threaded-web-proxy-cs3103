#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
class OneToManyRelationStore
{
public:
	// Direct Relation methods
	bool CheckRelation(T left, T right);
	void SetRelation(T left, T right);
	std::shared_ptr<std::unordered_set<T>> GetMany(T t);
	T GetOne(T t);
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllRelations();

	// Transitive Relation methods
	bool CheckTransitiveRelation(T left, T right);
	void SetTransitiveRelation(T left, T right);
	std::shared_ptr<std::unordered_set<T>> GetAllTransitiveMany(T t);
	std::shared_ptr<std::unordered_set<T>> GetAllTransitiveOne(T t);
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations();
private:
	std::vector<std::pair<T, T>> all_relations_;
	std::vector<std::pair<T, T>> all_transitive_relations_;
	std::unordered_map<T, std::unordered_set<T>> one_to_many_map_;
	std::unordered_map<T, T> many_to_one_map_;
};

template<typename T>
inline bool OneToManyRelationStore<T>::CheckRelation(T left, T right)
{
	return many_to_one_map_[right] == left;
}

template<typename T>
inline void OneToManyRelationStore<T>::SetRelation(T left, T right)
{
	// defensive checks
	assert(left < right);
	assert(many_to_one_map_.find(right) == many_to_one_map_.end());

	all_relations_.push_back(std::make_pair(left, right));
	one_to_many_map_[left].insert(right);
	many_to_one_map_[right] = left;
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToManyRelationStore<T>::GetMany(T t)
{
	if(one_to_many_map_.find(t) == one_to_many_map_.end())
	{
		return std::make_shared<std::unordered_set<T>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<T>>(one_to_many_map_[t]);
	}
}

template<typename T>
inline T OneToManyRelationStore<T>::GetOne(T t)
{
	if (many_to_one_map_.find(t) == many_to_one_map_.end())
	{
		return NULL;
	}
	else
	{
		return many_to_one_map_[t];
	}
}

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> OneToManyRelationStore<T>::GetAllRelations()
{
	return std::make_shared<std::vector<std::pair<T, T>>>(all_relations_);
}

template<typename T>
inline bool OneToManyRelationStore<T>::CheckTransitiveRelation(T left, T right)
{
	T next = right;
	auto iter = many_to_one_map_.find(next);
	while (iter != many_to_one_map_.end())
	{
		T one = many_to_one_map_[next];
		if (one == left)
		{
			return true;
		}
		next = one;
		iter = many_to_one_map_.find(next);
	}
	return false;
}

template<typename T>
inline void OneToManyRelationStore<T>::SetTransitiveRelation(T left, T right)
{
	std::pair<T, T> pair = std::make_pair(left, right);
	if (std::find(all_transitive_relations_.begin(), all_transitive_relations_.end(), pair) == all_transitive_relations_.end())
	{
		all_transitive_relations_.push_back(pair);
	}
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToManyRelationStore<T>::GetAllTransitiveMany(T t)
{
	std::shared_ptr<std::unordered_set<T>> all_many = std::make_shared<std::unordered_set<T>>();
	std::queue<T> queue;
	queue.push(t);
	while (!queue.empty())
	{
		T one = queue.front();
		queue.pop();
		auto iter = one_to_many_map_.find(one);
		if (iter == one_to_many_map_.end())
		{
			continue;
		}
		std::unordered_set<T>& many = one_to_many_map_[one];
		for (auto iter = many.begin(); iter != many.end(); ++iter)
		{
			all_many->insert(*iter);
			queue.push(*iter);
		}
	}
	return all_many;
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToManyRelationStore<T>::GetAllTransitiveOne(T t)
{
	std::shared_ptr<std::unordered_set<T>> all_one = std::make_shared<std::unordered_set<T>>();
	T next = t;
	auto iter = many_to_one_map_.find(next);
	while (iter != many_to_one_map_.end())
	{
		T one = many_to_one_map_[next];
		next = one;
		all_one->insert(next);
		iter = many_to_one_map_.find(next);
	}
	return all_one;
}

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> OneToManyRelationStore<T>::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<T, T>>>(all_transitive_relations_);
}
