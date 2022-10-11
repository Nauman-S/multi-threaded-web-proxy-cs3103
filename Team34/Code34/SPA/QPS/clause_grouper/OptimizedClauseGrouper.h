#pragma once

#include "ClauseGrouper.h"

class OptimizedClauseGrouper :
	public ClauseGrouper {
protected:
	void Group() override;

public:
	OptimizedClauseGrouper(std::vector<std::shared_ptr<Clause>> clauses, std::vector<std::string> synonyms)
		:ClauseGrouper{ clauses, synonyms } {
		Group();
	}


};