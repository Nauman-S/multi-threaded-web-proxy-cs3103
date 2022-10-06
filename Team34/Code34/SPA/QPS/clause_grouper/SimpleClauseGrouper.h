#pragma once

#include "ClauseGrouper.h"



/*
* This class will only create one clause group for each type of group. 
*/
class SimpleClauseGrouper 
	: public ClauseGrouper
{
protected:
	void Group() override;

public:
	SimpleClauseGrouper(std::vector<std::shared_ptr<Clause>> clauses, std::vector<std::string> synonyms)
		: ClauseGrouper{ clauses, synonyms } {
		Group();
	};
	
};

