#pragma once

#include <memory>
#include <unordered_set>

template <typename T>
class EntityManager
{
public:
	void AddEntity(T entity);
	bool IsEntity(T entity);
	std::shared_ptr<std::unordered_set<T>> GetAllEntities();
protected:
	std::unordered_set<T> entities_;
};

template<typename T>
inline void EntityManager<T>::AddEntity(T entity)
{
	entities_.insert(entity);
}

template<typename T>
inline bool EntityManager<T>::IsEntity(T entity)
{
	auto iter = entities_.find(entity);
	return iter == entities_.end();
}

template<typename T>
inline std::shared_ptr<std::unordered_set<T>> EntityManager<T>::GetAllEntities()
{
	return std::make_shared<std::unordered_set<T>>(entities_);
}

