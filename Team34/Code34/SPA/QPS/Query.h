#pragma once
#include "reference/Ref.h"
#include "relation/Rel.h"
#include "pattern/Pattern.h"
#include "Clause.h"
#include "DataRetriever.h"

#include <vector>
#include <unordered_map>
#include <string>
class Query
{
protected:
	std::vector<Ref> select_tuple_;
	std::vector<Rel> relations_;
	std::vector<Pattern> patterns_;

public:
	Query() {};

	explicit Query(std::vector<Ref> select_tuple) :select_tuple_{ select_tuple } {};

	Query(std::vector<Ref> select_tuple, std::vector<Rel> relations) : select_tuple_{ select_tuple }, relations_{ relations } {};

	Query(std::vector<Ref> select_tuple, std::vector<Pattern> patterns) : select_tuple_{ select_tuple }, patterns_{patterns} {};

	Query(std::vector<Ref> select_tuple, std::vector<Rel> relations, std::vector<Pattern> patterns)
		: select_tuple_{ select_tuple }, relations_{ relations }, patterns_{ patterns } {};

	std::vector<Rel>& GetRelations();
};

