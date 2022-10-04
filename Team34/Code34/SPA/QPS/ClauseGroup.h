#pragma once

#include "Clause.h"

class ClauseGroup
{
private:
	std::vector<Clause> clauses_;

public:
	ClauseGroup(std::vector<Clause> clauses) : clauses_{ clauses } {};

	std::vector<Clause> GetClauses() { return clauses_; };
};

