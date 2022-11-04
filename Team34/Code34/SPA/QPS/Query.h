#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include "reference/Ref.h"
#include "clause/relation/Rel.h"
#include "clause/pattern/Pattern.h"
#include "clause/with_clause/With.h"
#include "clause/Clause.h"
#include "DataRetriever.h"

using std::vector;
using std::shared_ptr;

class Query {
protected:
    shared_ptr<vector<shared_ptr<Ref>>> select_tuple_;
    shared_ptr<vector<shared_ptr<Rel>>> relations_;
    shared_ptr<vector<shared_ptr<Pattern>>> patterns_;
    shared_ptr<vector<shared_ptr<With>>> with_clauses_;
    bool is_boolean_;

public:
    Query() : select_tuple_{ nullptr }, relations_{ nullptr }, patterns_{ nullptr }, with_clauses_{ nullptr }, is_boolean_{ false } {};

    Query(shared_ptr< vector<shared_ptr<Rel>>> relations, shared_ptr< vector<shared_ptr<Pattern>>> patterns, shared_ptr<vector<shared_ptr<With>>> with_clauses)
        : relations_{ relations }, patterns_{ patterns }, with_clauses_{ with_clauses }, is_boolean_{ true } {
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

    shared_ptr<vector<shared_ptr<Rel>>> GetRelations() {
        return relations_;
    }

    shared_ptr<vector<shared_ptr<Pattern>>> GetPatterns() {
        return patterns_;
    }

    shared_ptr<vector<shared_ptr<With>>> GetWithClauses() {
        return with_clauses_;
    }

    shared_ptr<vector<shared_ptr<Clause>>> GetAllClauses();

    bool IsBoolean() {
        return is_boolean_;
    }
};

