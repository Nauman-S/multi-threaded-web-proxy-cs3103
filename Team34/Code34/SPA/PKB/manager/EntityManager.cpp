#include "EntityManager.h"

void EntityManager::AddEntity(T entity)
{
	entities_.insert(entity);
}

bool EntityManager::IsEntity(T entity)
{
	auto iter = entities_.find(entity);
	return iter == entities_.end();
}

std::shared_ptr<std::unordered_set<T>> EntityManager::GetAllEntities()
{
	return std::make_shared<std::unordered_set<T>>(entities_);
}