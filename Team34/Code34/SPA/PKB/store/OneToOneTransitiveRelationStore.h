#pragma once

#include <memory>
#include <vector>

#include "OneToOneRelationStore.h"

template <typename S>
class OneToOneTransitiveRelationStore: public OneToOneRelationStore<S>
{
public:
	void SetTransitiveRelation(S left, S right);
	bool CheckTransistiveRelation(S left, S right);
	std::shared_ptr<std::vector<S>> GetAllRHSByLHS(S left);
	std::shared_ptr<std::vector<S>> GetAllLHSByRHS(S right);
	std::shared_ptr<std::vector<std::pair<S, S>>> GetAllTransitiveRelations();
private:
	std::vector<std::pair<S, S>> all_left_right_transitive_pairs_;
};

template<typename S>
inline void OneToOneTransitiveRelationStore<S>::SetTransitiveRelation(S left, S right)
{
	all_left_right_transitive_pairs_.push_back(std::make_pair(left, right));
}

template<typename S>
inline bool OneToOneTransitiveRelationStore<S>::CheckTransistiveRelation(S left, S right)
{
	auto iter = left_to_right_map_.find(left);
	while (iter != left_to_right_map_.end())
	{
		S next = left_to_right_map_[left];
		if (next == right)
		{
			return true;
		}
		iter = left_to_right_map_.find(next);
	}
	return false;
}

template<typename S>
inline std::shared_ptr<std::vector<S>> OneToOneTransitiveRelationStore<S>::GetAllRHSByLHS(S left)
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
inline std::shared_ptr<std::vector<S>> OneToOneTransitiveRelationStore<S>::GetAllLHSByRHS(S right)
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
inline std::shared_ptr<std::vector<std::pair<S, S>>> OneToOneTransitiveRelationStore<S>::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<S, S>>>(all_left_right_transitive_pairs_);
}
