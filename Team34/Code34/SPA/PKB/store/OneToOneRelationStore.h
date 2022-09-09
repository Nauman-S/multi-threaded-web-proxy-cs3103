#pragma once

#include <cassert>
#include <memory>
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
	// Transitive one to one relations
	bool CheckTransistiveRelation(S left, S right);
	void SetTransitiveRelation(S left, S right);
	std::shared_ptr<std::vector<S>> GetAllRHSByLHS(S left);
	std::shared_ptr<std::vector<S>> GetAllLHSByRHS(S right);
	std::shared_ptr<std::vector<std::pair<S, S>>> GetAllTransitiveRelations();
private:
	std::unordered_map<S, S> left_to_right_map_;
	std::unordered_map<S, S> right_to_left_map_;
	std::vector<std::pair<S, S>> all_left_right_pairs_;
	std::vector<std::pair<S, S>> all_left_right_transitive_pairs_;
};

template<typename S>
inline bool OneToOneRelationStore<S>::CheckRelation(S left, S right)
{
	return left_to_right_map_.find(left) != right_to_left_map_.end();
}

template<typename S>
inline void OneToOneRelationStore<S>::SetRelation(S left, S right)
{
	assert(left_to_right_map_.find(left) == left_to_right_map_.end());
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

template<typename S>
inline bool OneToOneRelationStore<S>::CheckTransistiveRelation(S left, S right)
{
	auto iter = left_to_right_map_.find(left);
	S next = left;
	while (iter != left_to_right_map_.end())
	{
		next = left_to_right_map_[next];
		std::cout << next << std::endl;
		if (next == right)
		{
			return true;
		}
		iter = left_to_right_map_.find(next);
	}
	return false;
}

template<typename S>
inline void OneToOneRelationStore<S>::SetTransitiveRelation(S left, S right)
{
	all_left_right_transitive_pairs_.push_back(std::make_pair(left, right));
}

template<typename S>
inline std::shared_ptr<std::vector<S>> OneToOneRelationStore<S>::GetAllRHSByLHS(S left)
{
	std::shared_ptr<std::vector<S>> all_rhs = std::make_shared<std::vector<S>>();
	auto iter = left_to_right_map_.find(left);
	while (iter != left_to_right_map_.end())
	{
		S right = left_to_right_map_[left];
		all_rhs->push_back(right);
		iter = left_to_right_map_.find(right);
	}
	return all_rhs;
}

template<typename S>
inline std::shared_ptr<std::vector<S>> OneToOneRelationStore<S>::GetAllLHSByRHS(S right)
{
	std::shared_ptr<std::vector<S>> all_lhs = std::make_shared<std::vector<S>>();
	auto iter = right_to_left_map_.find(right);
	while (iter != right_to_left_map_.end())
	{
		S left = right_to_left_map[right];
		all_lhs->push_back(left);
		iter = right_to_left_map_.find(left);
	}
	return all_lhs;
}

template<typename S>
inline std::shared_ptr<std::vector<std::pair<S, S>>> OneToOneRelationStore<S>::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<S, S>>>(all_left_right_transitive_pairs_);
}
