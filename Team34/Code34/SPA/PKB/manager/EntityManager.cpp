#include "EntityManager.h"

template<typename T>
std::unordered_set<T> EntityManager<T>::entities_;

template <typename T>
void EntityManager<T>::AddEntity(T entity)
{
	entities_.insert(entity);
}

template <typename T>
bool EntityManager<T>::IsEntity(T entity)
{
	auto iter = entities_.find(entity);
	return iter == entities_.end();
}

template <typename T>
std::shared_ptr<std::unordered_set<T>> EntityManager<T>::GetAllEntities()
{
	return std::make_shared<std::unordered_set<T>>(entities_);
}