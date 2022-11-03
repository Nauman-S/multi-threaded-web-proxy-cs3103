#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

template <typename S, typename T>
class OneToOneRelationStore {
public:
	// Direct relation methods
	void SetRelation(S left, T right);
	bool CheckRelation(S left, T right);
	bool IsEmpty();
	std::shared_ptr<std::unordered_set<T>> GetRHSByLHS(S left);
	std::shared_ptr<std::unordered_set<S>> GetLHSByRHS(T right);
	std::shared_ptr<std::unordered_set<S>> GetAllLHS();
	std::shared_ptr<std::unordered_set<T>> GetAllRHS();
	std::shared_ptr<std::vector<std::pair<S, T>>> GetAllRelations();
	void Clear();
protected:
	std::unordered_map<S, T> left_to_right_map_;
	std::unordered_map<T, S> right_to_left_map_;
	std::vector<std::pair<S, T>> all_relations_;
};

template <typename S, typename T>
inline void OneToOneRelationStore<S, T>::SetRelation(S left, T right) {
	// defensive check to prevent adding duplicate entries
	if (left_to_right_map_.find(left) != left_to_right_map_.end() || right_to_left_map_.find(right) != right_to_left_map_.end()) {
		return;
	}
	left_to_right_map_[left] = right;
	right_to_left_map_[right] = left;
	all_relations_.push_back(std::make_pair(left, right));
}

template <typename S, typename T>
inline bool OneToOneRelationStore<S, T>::CheckRelation(S left, T right) {
	if (left_to_right_map_.find(left) == left_to_right_map_.end()) {
		return false;
	}
	return left_to_right_map_[left] == right;
}

template <typename S, typename T>
inline bool OneToOneRelationStore<S, T>::IsEmpty() {
	return all_relations_.empty();
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToOneRelationStore<S, T>::GetRHSByLHS(S left) {
	std::shared_ptr<std::unordered_set<T>> rhs = std::make_shared<std::unordered_set<T>>();
	if (left_to_right_map_.find(left) != left_to_right_map_.end()) {
		rhs->insert(left_to_right_map_[left]);
	}
	return rhs;
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<S>> OneToOneRelationStore<S, T>::GetLHSByRHS(T right) {
	std::shared_ptr<std::unordered_set<S>> lhs = std::make_shared<std::unordered_set<S>>();
	if (right_to_left_map_.find(right) != right_to_left_map_.end()) {
		lhs->insert(right_to_left_map_[right]);
	}
	return lhs;
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<S>> OneToOneRelationStore<S, T>::GetAllLHS() {
	std::shared_ptr<std::unordered_set<S>> all_lhs = std::make_shared<std::unordered_set<T>>();
	for (auto iter = all_relations_.begin(); iter != all_relations_.end(); ++iter) {
		all_lhs->insert(iter->first);
	}
	return all_lhs;
}

template <typename S, typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToOneRelationStore<S, T>::GetAllRHS() {
	std::shared_ptr<std::unordered_set<T>> all_rhs = std::make_shared<std::unordered_set<T>>();
	for (auto iter = all_relations_.begin(); iter != all_relations_.end(); ++iter) {
		all_rhs->insert(iter->second);
	}
	return all_rhs;
}

template <typename S, typename T>
inline std::shared_ptr<std::vector<std::pair<S, T>>> OneToOneRelationStore<S, T>::GetAllRelations() {
	return std::make_shared<std::vector<std::pair<S, T>>>(all_relations_);
}

template<typename S, typename T>
inline void OneToOneRelationStore<S, T>::Clear() {
	left_to_right_map_.clear();
	right_to_left_map_.clear();
	all_relations_.clear();
}
