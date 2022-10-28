#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

#include "Clause.h"

class ClauseGroup
{
private:
	std::vector<std::shared_ptr<Clause>> clauses_;

public:
	explicit ClauseGroup(std::vector<std::shared_ptr<Clause>> clauses) : clauses_{ clauses } {}

	std::vector<std::shared_ptr<Clause>> GetClauses() { return clauses_; }

	std::shared_ptr<std::unordered_set<std::string>> GetSynSet();
};

