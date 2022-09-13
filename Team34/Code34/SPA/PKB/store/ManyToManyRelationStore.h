#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename S, typename T>
class ManyToManyRelationStore
{
public:
	bool CheckRelation(S s, T t);
	std::shared_ptr<std::vector<std::pair<S, T>>> GetAllRelations();
	std::shared_ptr<std::unordered_set<S>> GetAllLHS();
	void SetRelation(S s, T t);
	std::shared_ptr<std::unordered_set<T>> GetRHSByLHS(S s);
	std::shared_ptr<std::unordered_set<S>> GetLHSByRHS(T t);
private:
	std::unordered_map<S, std::unordered_set<T>> s_to_t_map_;
	std::unordered_map<T, std::unordered_set<S>> t_to_s_map_;
};

template<typename S,typename T>
inline bool ManyToManyRelationStore<S, T>::CheckRelation(S s, T t)
{
	auto iter = t_to_s_map_.find(t);
	if (iter != t_to_s_map_.end())
	{
		// found T type key
		return t_to_s_map_[t].find(s) != t_to_s_map_[t].end();
	}
	return false;
}

template<typename S, typename T>
inline std::shared_ptr<std::vector<std::pair<S, T>>> ManyToManyRelationStore<S, T>::GetAllRelations()
{
	std::shared_ptr<std::vector<std::pair<S, T>>> all_relations = std::make_shared<std::vector<std::pair<S,T>>>();
	for (const auto& s : s_to_t_map_)
	{
		for (auto iter = s.second.begin(); iter != s.second.end(); iter++)
		{
			all_relations->push_back(std::make_pair(s.first, *iter));
		}
	}
	return all_relations;
}

template<typename S, typename T>
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
inline void ManyToManyRelationStore<S, T>::SetRelation(S s, T t)
{
	s_to_t_map_[s].insert(t);
	t_to_s_map_[t].insert(s);
}

template<typename S, typename T>
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

template<typename S, typename T>
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