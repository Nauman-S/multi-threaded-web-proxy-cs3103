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
private:
	static std::unordered_set<T> entities_;
};