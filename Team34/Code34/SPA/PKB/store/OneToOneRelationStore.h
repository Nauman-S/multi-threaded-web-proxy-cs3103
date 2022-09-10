#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <vector>

template <typename T>
class OneToOneRelationStore
{
public:
	bool CheckRelation(T left, T right);
	void SetRelation(T left, T right);
	T GetRHSByLHS(T left);
	T GetLHSByRHS(T right);
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllRelations();
	// Transitive one to one relations
	bool CheckTransistiveRelation(T left, T right);
	void SetTransitiveRelation(T left, T right);
	std::shared_ptr<std::vector<T>> GetAllRHSByLHS(T left);
	std::shared_ptr<std::vector<T>> GetAllLHSByRHS(T right);
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations();
private:
	std::unordered_map<T, T> left_to_right_map_;
	std::unordered_map<T, T> right_to_left_map_;
	std::vector<std::pair<T, T>> all_left_right_pairs_;
	std::vector<std::pair<T, T>> all_left_right_transitive_pairs_;
};

template<typename T>
inline bool OneToOneRelationStore<T>::CheckRelation(T left, T right)
{
	if (left_to_right_map_.find(left) != left_to_right_map_.end())
	{
		return left_to_right_map_[left] == right;
	}
	return false;
}

template<typename T>
inline void OneToOneRelationStore<T>::SetRelation(T left, T right)
{
	assert(left_to_right_map_.find(left) == left_to_right_map_.end());
	assert(right_to_left_map_.find(right) == right_to_left_map_.end());
	left_to_right_map_[left] = right;
	right_to_left_map_[right] = left;
	all_left_right_pairs_.push_back(std::make_pair(left, right));
}

template<typename T>
inline T OneToOneRelationStore<T>::GetRHSByLHS(T left)
{
	if (left_to_right_map_.find(left) == left_to_right_map_.end())
	{
		return NULL;
	}
	else
	{
		return left_to_right_map_[left];
	}
}

template<typename T>
inline T OneToOneRelationStore<T>::GetLHSByRHS(T right)
{
	if (right_to_left_map_.find(right) == right_to_left_map_.end())
	{
		return NULL;
	}
	else
	{
		return right_to_left_map_[right];
	}
}

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> OneToOneRelationStore<T>::GetAllRelations()
{
	return std::make_shared<std::vector<std::pair<T, T>>>(all_left_right_pairs_);
}

template<typename T>
inline bool OneToOneRelationStore<T>::CheckTransistiveRelation(T left, T right)
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

template<typename T>
inline void OneToOneRelationStore<T>::SetTransitiveRelation(T left, T right)
{
	all_left_right_transitive_pairs_.push_back(std::make_pair(left, right));
}

template<typename T>
inline std::shared_ptr<std::vector<T>> OneToOneRelationStore<T>::GetAllRHSByLHS(T left)
{
	return GetAllHelper(left, left_to_right_map_);
}

template<typename T>
inline std::shared_ptr<std::vector<T>> OneToOneRelationStore<T>::GetAllLHSByRHS(T right)
{
	return GetAllHelper(right, right_to_left_map_);
}

template<typename T>
inline std::shared_ptr<std::vector<T>> GetAllHelper(T start, std::unordered_map<T, T>& map)
{
	std::shared_ptr<std::vector<T>> all = std::make_shared<std::vector<T>>();
	auto iter = map.find(start);
	T next = start;
	while (iter != map.end())
	{
		next = map[next];
		all->push_back(next);
		iter = map.find(next);
	}
	return all;
}

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> OneToOneRelationStore<T>::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<T, T>>>(all_left_right_transitive_pairs_);
}