#pragma once

#include "relation/UsesSRel.h"
#include "relation/UsesPRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/ModifiesPRel.h"
#include "QueryResult.h"

class DataRetriever
{
public:
	const QueryResult& retrieve(const ModifiesPRel rel);

	const QueryResult& retrieve(const UsesPRel rel);

	const QueryResult& retrieve(const ModifiesSRel rel);

	const QueryResult& retrieve(const ModifiesPRel rel);
};

