#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename S, typename T>
class OneToManyRelationStore
{
public:
	// Direct Relation methods
	void SetRelation(S left, T right);
	bool CheckRelation(S left, T right);
	bool IsEmpty();
	std::shared_ptr<std::unordered_set<T>> GetMany(S s);
	std::shared_ptr<std::unordered_set<S>> GetOne(T t);
	std::shared_ptr<std::unordered_set<S>> GetAllLHS();
	std::shared_ptr<std::unordered_set<T>> GetAllRHS();
	std::shared_ptr<std::vector<std::pair<S, T>>> GetAllRelations();
protected:
	std::vector<std::pair<S, T>> all_relations_;
	std::unordered_map<S, std::unordered_set<T>> one_to_many_map_;
	std::unordered_map<T, S> many_to_one_map_;
};

template <typename S, typename T>
inline void OneToManyRelationStore<S, T>::SetRelation(S left, T right)
{
	// defensive check to prevent adding duplicate entries
	if (many_to_one_map_.find(right) != many_to_one_map_.end() || one_to_many_map_[left].find(right) != one_to_many_map_[left].end())
	{
		return;
	}
	all_relations_.push_back(std::make_pair(left, right));
	one_to_many_map_[left].insert(right);
	many_to_one_map_[right] = left;
}

template <typename S, typename T>
inline bool OneToManyRelationStore<S, T>::CheckRelation(S left, T right)
{
	return many_to_one_map_[right] == left;
}

template <typename S, typename T>
inline bool OneToManyRelationStore<S, T>::IsEmpty()
{
	return all_relations_.empty();
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToManyRelationStore<S, T>::GetMany(S s)
{
	if (one_to_many_map_.find(s) == one_to_many_map_.end())
	{
		return std::make_shared<std::unordered_set<T>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<T>>(one_to_many_map_[s]);
	}
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<S>> OneToManyRelationStore<S, T>::GetOne(T t)
{
	std::shared_ptr<std::unordered_set<S>> parent = std::make_shared<std::unordered_set<S>>();
	if (many_to_one_map_.find(t) != many_to_one_map_.end())
	{
		parent->insert(many_to_one_map_[t]);
	}
	return parent;
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<S>> OneToManyRelationStore<S, T>::GetAllLHS()
{
	std::shared_ptr<std::unordered_set<S>> all_lhs = std::make_shared<std::unordered_set<S>>();
	for (auto iter = all_relations_.begin(); iter != all_relations_.end(); ++iter)
	{
		all_lhs->insert(iter->first);
	}
	return all_lhs;
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToManyRelationStore<S, T>::GetAllRHS()
{
	std::shared_ptr<std::unordered_set<T>> all_rhs = std::make_shared<std::unordered_set<T>>();
	for (auto iter = all_relations_.begin(); iter != all_relations_.end(); ++iter)
	{
		all_rhs->insert(iter->second);
	}
	return all_rhs;
}

template <typename S, typename T>
inline std::shared_ptr<std::vector<std::pair<S, T>>> OneToManyRelationStore<S, T>::GetAllRelations()
{
	return std::make_shared<std::vector<std::pair<S, T>>>(all_relations_);
}
