#pragma once

#include <memory>

#include "Clause.h"

class ClauseGroup
{
private:
	std::shared_ptr<std::vector<Clause>> clauses_;

public:
	ClauseGroup(std::shared_ptr<std::vector<Clause>> clauses) : clauses_{ clauses } {};

	std::shared_ptr<std::vector<Clause>> GetClauses() { return clauses_; };
};

