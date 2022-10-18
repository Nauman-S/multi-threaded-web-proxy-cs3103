#pragma once

#include "OneToManyRelationStore.h"

template <typename T>
class OneToManyTransitiveRelationStore : public OneToManyRelationStore<T, T> {
public:
	// Transitive Relation methods
	bool CheckTransitiveRelation(T left, T right);
	std::shared_ptr<std::unordered_set<T>> GetAllTransitiveMany(T t);
	std::shared_ptr<std::unordered_set<T>> GetAllTransitiveOne(T t);
	virtual std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations() = 0;
};

template <typename T>
inline bool OneToManyTransitiveRelationStore<T>::CheckTransitiveRelation(T left, T right) {
	T next = right;
	auto iter = many_to_one_map_.find(next);
	while (iter != many_to_one_map_.end()) {
		T one = many_to_one_map_[next];
		if (one == left) {
			return true;
		}
		next = one;
		iter = many_to_one_map_.find(next);
	}
	return false;
}

template <typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToManyTransitiveRelationStore<T>::GetAllTransitiveMany(T t) {
	std::shared_ptr<std::unordered_set<T>> all_many = std::make_shared<std::unordered_set<T>>();
	std::queue<T> queue;
	queue.push(t);
	while (!queue.empty()) {
		T one = queue.front();
		queue.pop();
		auto iter = one_to_many_map_.find(one);
		if (iter == one_to_many_map_.end()) {
			continue;
		}
		std::unordered_set<T>& many = one_to_many_map_[one];
		for (auto iter = many.begin(); iter != many.end(); ++iter) {
			all_many->insert(*iter);
			queue.push(*iter);
		}
	}
	return all_many;
}

template <typename T>
inline std::shared_ptr<std::unordered_set<T>> OneToManyTransitiveRelationStore<T>::GetAllTransitiveOne(T t) {
	std::shared_ptr<std::unordered_set<T>> all_one = std::make_shared<std::unordered_set<T>>();
	T next = t;
	auto iter = many_to_one_map_.find(next);
	while (iter != many_to_one_map_.end()) {
		T one = many_to_one_map_[next];
		next = one;
		all_one->insert(next);
		iter = many_to_one_map_.find(next);
	}
	return all_one;
}
