#pragma once
#include "reference/Ref.h"
#include "relation/Rel.h"
#include "pattern/Pattern.h"
#include "Clause.h"
#include "DataRetriever.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

using std::vector;
using std::shared_ptr;

class Query
{
protected:
	shared_ptr<vector<shared_ptr<Ref>>> select_tuple_;
	shared_ptr< vector<shared_ptr<Rel>>> relations_;
	shared_ptr< vector<shared_ptr<Pattern>>> patterns_;

public:
	Query() {};

	explicit Query(shared_ptr<vector<shared_ptr<Ref>>> select_tuple)
		: select_tuple_{ select_tuple_ } {};
	

	Query(shared_ptr<vector<shared_ptr<Ref>>> select_tuple, shared_ptr< vector<shared_ptr<Rel>>> relations)
		: select_tuple_{ select_tuple }, relations_{ relations } {};

	Query(shared_ptr<vector<shared_ptr<Ref>>> select_tuple, shared_ptr< vector<shared_ptr<Pattern>>> patterns)
		: select_tuple_{ select_tuple }, patterns_{patterns} {};

	Query(shared_ptr<vector<shared_ptr<Ref>>> select_tuple, shared_ptr< vector<shared_ptr<Rel>>> relations, shared_ptr< vector<shared_ptr<Pattern>>> patterns)
		: select_tuple_{ select_tuple }, relations_{ relations }, patterns_{ patterns } {};

	shared_ptr<vector<shared_ptr<Ref>>> GetSelectTuple() {
		return select_tuple_;
	}

	shared_ptr< vector<shared_ptr<Rel>>> GetRelations() {
		return relations_;
	}

	shared_ptr< vector<shared_ptr<Pattern>>> GetPatterns() {
		return patterns_;
	}
};

