#pragma once

#include "ManyToManyTransitiveRelationStore.h"

template <typename T>
class ManyToManyNextStore : public ManyToManyTransitiveRelationStore<T>
{
public:
	std::shared_ptr<std::vector<std::pair<T, T>>> GetAllTransitiveRelations();
};

template<typename T>
inline std::shared_ptr<std::vector<std::pair<T, T>>> ManyToManyNextStore<T>::GetAllTransitiveRelations()
{
	return std::shared_ptr<std::vector<std::pair<T, T>>>();
}
