#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename S, typename T>
class ManyToManyRelationStore
{
public:
	void SetRelation(S s, T t);
	bool CheckRelation(S s, T t);
	bool IsEmpty();
	std::shared_ptr<std::unordered_set<T>> GetRHSByLHS(S s);
	std::shared_ptr<std::unordered_set<S>> GetLHSByRHS(T t);
	std::shared_ptr<std::unordered_set<S>> GetAllLHS();
	std::shared_ptr<std::unordered_set<T>> GetAllRHS();
	std::shared_ptr<std::vector<std::pair<S, T>>> GetAllRelations();
	void Clear();
protected:
	std::vector<std::pair<S, T>> all_relations_;
	std::unordered_map<S, std::unordered_set<T>> s_to_t_map_;
	std::unordered_map<T, std::unordered_set<S>> t_to_s_map_;
};

template <typename S, typename T>
inline void ManyToManyRelationStore<S, T>::SetRelation(S s, T t)
{
	// defensive check to prevent adding duplicate entries
	if (s_to_t_map_[s].find(t) != s_to_t_map_[s].end() || t_to_s_map_[t].find(s) != t_to_s_map_[t].end())
	{
		return;
	}
	s_to_t_map_[s].insert(t);
	t_to_s_map_[t].insert(s);
	all_relations_.push_back(std::make_pair(s, t));
}

template <typename S, typename T>
inline bool ManyToManyRelationStore<S, T>::CheckRelation(S s, T t)
{
	auto iter = t_to_s_map_.find(t);
	if (iter != t_to_s_map_.end())
	{
		return t_to_s_map_[t].find(s) != t_to_s_map_[t].end();
	}
	return false;
}

template<typename S, typename T>
inline bool ManyToManyRelationStore<S, T>::IsEmpty()
{
	return all_relations_.empty();
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<T>> ManyToManyRelationStore<S, T>::GetRHSByLHS(S s)
{
	auto iter = s_to_t_map_.find(s);
	if (iter == s_to_t_map_.end())
	{
		return std::make_shared<std::unordered_set<T>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<T>>(s_to_t_map_[s]);
	}
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<S>> ManyToManyRelationStore<S, T>::GetLHSByRHS(T t)
{
	auto iter = t_to_s_map_.find(t);
	if (iter == t_to_s_map_.end())
	{
		return std::make_shared<std::unordered_set<S>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<S>>(t_to_s_map_[t]);
	}
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<S>> ManyToManyRelationStore<S, T>::GetAllLHS()
{
	std::shared_ptr<std::unordered_set<S>> all_lhs = std::make_shared<std::unordered_set<S>>();
	for (auto kv : s_to_t_map_)
	{
		all_lhs->insert(kv.first);
	}
	return all_lhs;
}

template<typename S, typename T>
inline std::shared_ptr<std::unordered_set<T>> ManyToManyRelationStore<S, T>::GetAllRHS()
{
	std::shared_ptr<std::unordered_set<T>> all_rhs = std::make_shared<std::unordered_set<T>>();
	for (auto kv : t_to_s_map_)
	{
		all_rhs->insert(kv.first);
	}
	return all_rhs;
}

template <typename S, typename T>
inline std::shared_ptr<std::vector<std::pair<S, T>>> ManyToManyRelationStore<S, T>::GetAllRelations()
{
	return std::make_shared<std::vector<std::pair<S, T>>>(all_relations_);
}

template<typename S, typename T>
inline void ManyToManyRelationStore<S, T>::Clear()
{
	all_relations_.clear();
	s_to_t_map_.clear();
	t_to_s_map_.clear();
}
