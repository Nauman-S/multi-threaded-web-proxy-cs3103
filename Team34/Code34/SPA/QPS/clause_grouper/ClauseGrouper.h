#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../ClauseGroup.h"
#include "../Clause.h"

class ClauseGrouper
{
protected:
	std::vector<std::shared_ptr<Clause>> clauses_;
	std::vector<std::string> select_synonyms_;
	std::shared_ptr<ClauseGroup> group_wo_syn_;
	std::vector<std::shared_ptr<ClauseGroup>> groups_wo_select_syn_;
	std::vector<std::shared_ptr<ClauseGroup>> groups_w_select_syn_;

	

	virtual void Group() = 0;
	bool AreSelectSynsIn(std::vector<std::string> syns);
	
public:
	/*static std::shared_ptr<ClauseGrouper> CreateClauseGrouper(std::vector<Clause> clauses, std::vector<std::string> synonyms) {
		return std::make_shared<ClauseGrouper>(clauses, synonyms);
	}*/

	ClauseGrouper(std::vector<std::shared_ptr<Clause>> clauses, std::vector<std::string> synonyms)
		: clauses_{ clauses }, select_synonyms_{ synonyms } {
	};

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

