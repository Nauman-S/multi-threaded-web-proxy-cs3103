#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename S, typename T>
class ManyToOneRelationStore
{
public:
	// Direct Relation methods
	bool CheckRelation(S left, T right);
	void SetRelation(S left, T right);
	std::shared_ptr<std::unordered_set<S>> GetMany(T t);
	std::shared_ptr<T> GetOne(S s);
	std::shared_ptr<std::vector<std::pair<S, T>>> GetAllRelations();
	std::shared_ptr<std::unordered_set<S>> GetAllLHS();
	std::shared_ptr<std::unordered_set<T>> GetAllRHS();
	bool IsEmpty();
protected:
	std::vector<std::pair<S, T>> all_relations_;
	std::unordered_map<S, T> many_to_one_map_;
	std::unordered_map<T, std::unordered_set<S>> one_to_many_map_;
};

template<typename S, typename T>
inline bool ManyToOneRelationStore<S, T>::CheckRelation(S left, T right)
{
	return many_to_one_map_[left] == right;
}

template<typename S, typename T>
inline void ManyToOneRelationStore<S, T>::SetRelation(S left, T right)
{
	// defensive checks
	assert(many_to_one_map_.find(left) == many_to_one_map_.end());

	all_relations_.push_back(std::make_pair(left, right));
	many_to_one_map_[left] = right;
	one_to_many_map_[right].insert(left);
}

template<typename S, typename T>
inline std::shared_ptr<std::unordered_set<S>> ManyToOneRelationStore<S, T>::GetMany(T t)
{
	if (one_to_many_map_.find(t) == one_to_many_map_.end())
	{
		return std::make_shared<std::unordered_set<S>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<S>>(one_to_many_map_[t]);
	}
}

template<typename S, typename T>
inline std::shared_ptr<T> ManyToOneRelationStore<S, T>::GetOne(S s)
{
	if (many_to_one_map_.find(s) == many_to_one_map_.end())
	{
		return std::make_shared<T>();
	}
	else
	{
		return std::make_shared<T>(many_to_one_map_[s]);
	}
}

template<typename S, typename T>
inline std::shared_ptr<std::vector<std::pair<S, T>>> ManyToOneRelationStore<S, T>::GetAllRelations()
{
	return std::make_shared<std::vector<std::pair<S, T>>>(all_relations_);
}

template<typename S, typename T>
inline std::shared_ptr<std::unordered_set<S>> ManyToOneRelationStore<S, T>::GetAllLHS()
{
	std::shared_ptr<std::unordered_set<S>> all_lhs = std::make_shared<std::unordered_set<S>>();
	for (auto iter = all_relations_.begin(); iter != all_relations_.end(); ++iter)
	{
		all_lhs->insert(iter->first);
	}
	return all_lhs;
}

template<typename S, typename T>
inline std::shared_ptr<std::unordered_set<T>> ManyToOneRelationStore<S, T>::GetAllRHS()
{
	std::shared_ptr<std::unordered_set<T>> all_rhs = std::make_shared<std::unordered_set<T>>();
	for (auto iter = all_relations_.begin(); iter != all_relations_.end(); ++iter)
	{
		all_rhs->insert(iter->second);
	}
	return all_rhs;
}

template<typename S, typename T>
inline bool ManyToOneRelationStore<S, T>::IsEmpty()
{
	return all_relations_.empty();
}