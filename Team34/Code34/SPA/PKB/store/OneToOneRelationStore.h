#pragma once

#include <cassert>
#include <unordered_map>
#include <vector>

template <typename S>
class OneToOneRelationStore
{
public:
	bool CheckRelation(S left, S right);
	void SetRelation(S left, S right);
	S GetRHSByLHS(S left);
	S GetLHSByRHS(S right);
	std::shared_ptr<std::vector<std::pair<S, S>>> GetAllRelations();
protected:
	std::unordered_map<S, S> left_to_right_map_;
	std::unordered_map<S, S> right_to_left_map_;
	std::vector<std::pair<S, S>> all_left_right_pairs_;
};

template<typename S>
inline bool OneToOneRelationStore<S>::CheckRelation(S left, S right)
{
	return left_to_right_map_.find(left) != right_to_left_map_.end();
}

template<typename S>
inline void OneToOneRelationStore<S>::SetRelation(S left, S right)
{
	assert(left_to_right_map_.find(left) == right_to_left_map_.end());
	assert(right_to_left_map_.find(right) == right_to_left_map_.end());
	left_to_right_map_[left] = right;
	right_to_left_map_[right] = left;
	all_left_right_pairs_.push_back(std::make_pair(left, right));
}

template<typename S>
inline S OneToOneRelationStore<S>::GetRHSByLHS(S left)
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

template<typename S>
inline S OneToOneRelationStore<S>::GetLHSByRHS(S right)
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

template<typename S>
inline std::shared_ptr<std::vector<std::pair<S, S>>> OneToOneRelationStore<S>::GetAllRelations()
{
	return std::make_shared<std::vector<std::pair<S, S>>>(all_left_right_pairs_);
}
