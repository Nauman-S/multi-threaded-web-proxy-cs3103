#pragma once
#include "reference/Ref.h"
#include "relation/Rel.h"
#include "pattern/Pattern.h"
#include "with_clause/With.h"
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
	shared_ptr<vector<shared_ptr<Rel>>> relations_;
	shared_ptr<vector<shared_ptr<Pattern>>> patterns_;
	shared_ptr<vector<shared_ptr<With>>> with_clauses_;
	bool is_boolean_;

public:
	Query() {};

	Query(shared_ptr< vector<shared_ptr<Rel>>> relations, shared_ptr< vector<shared_ptr<Pattern>>> patterns, shared_ptr<vector<shared_ptr<With>>> with_clauses)
		: relations_{ relations }, patterns_{ patterns }, with_clauses_{with_clauses}, is_boolean_{true} {
		select_tuple_ = std::make_shared<vector<shared_ptr<Ref>>>();
	};


	Query(shared_ptr<vector<shared_ptr<Ref>>> select_tuple, shared_ptr< vector<shared_ptr<Rel>>> relations, 
		shared_ptr< vector<shared_ptr<Pattern>>> patterns, shared_ptr<vector<shared_ptr<With>>> with_clauses)
		: select_tuple_{ select_tuple }, relations_{ relations }, patterns_{ patterns }, with_clauses_{ with_clauses } {
		is_boolean_ = (select_tuple->size() == 0);
	};

	shared_ptr<vector<shared_ptr<Ref>>> GetSelectTuple() {
		return select_tuple_;
	}

	std::vector<std::string> GetSelectSynonyms();

	shared_ptr< vector<shared_ptr<Rel>>> GetRelations() {
		return relations_;
	}

	shared_ptr< vector<shared_ptr<Pattern>>> GetPatterns() {
		return patterns_;
	}

	shared_ptr< vector<shared_ptr<With>>> GetWithClauses() {
		return with_clauses_;
	}

	bool IsBoolean() {
		return is_boolean_;
	}
};

