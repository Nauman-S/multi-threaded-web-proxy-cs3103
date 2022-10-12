#pragma once

#include "ClauseGrouper.h"

class OptimizedClauseGrouper :
	public ClauseGrouper {
private:
	std::vector<std::shared_ptr<Clause>> OptimizeOrderWithinGroup(std::vector<std::shared_ptr<Clause>>);
	std::vector<std::shared_ptr<Clause>> AddToWaitingClauses();

protected:
	void Group() override;
public:
	OptimizedClauseGrouper(std::vector<std::shared_ptr<Clause>> clauses, std::vector<std::string> synonyms)
		:ClauseGrouper{ clauses, synonyms } {
		Group();
	}

};