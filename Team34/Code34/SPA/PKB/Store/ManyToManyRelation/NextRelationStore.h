#pragma once

#include "ManyToManyTransitiveRelationStore.h"

template <typename T>
class NextRelationStore : public ManyToManyTransitiveRelationStore<T>
{
public:
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations();
};

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> NextRelationStore<T>::GetAllTransitiveRelations()
{
	return std::shared_ptr<std::vector<std::pair<T, T>>>();
}
