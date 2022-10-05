#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../ClauseGroup.h"
#include "../Clause.h"

class ClauseGrouper
{
protected:
	std::shared_ptr<std::vector<Clause>> clauses_;
	std::vector<std::string> synonyms_;
	std::shared_ptr<ClauseGroup> group_wo_syn_;
	std::vector<std::shared_ptr<ClauseGroup>> groups_wo_select_syn_;
	std::vector<std::shared_ptr<ClauseGroup>> groups_w_select_syn_;

	ClauseGrouper(std::shared_ptr<std::vector<Clause>> clauses, std::vector<std::string> synonyms)
		: clauses_{ clauses }, synonyms_{synonyms} {};


public:
	/*static std::shared_ptr<ClauseGrouper> CreateClauseGrouper(std::vector<Clause> clauses, std::vector<std::string> synonyms) {
		return std::make_shared<ClauseGrouper>(clauses, synonyms);
	}*/

	virtual void Group() = 0;

	std::shared_ptr<ClauseGroup> GetClauseGroupWoSyn() {
		return group_wo_syn_;
	}
	
	std::vector<std::shared_ptr<ClauseGroup>> GetClauseGroupsWoSelectSyn() {
		return groups_wo_select_syn_;
	}

	std::vector<std::shared_ptr<ClauseGroup>> GetClauseGroupsWithSelectSyn() {
		return groups_w_select_syn_;
	}

};

