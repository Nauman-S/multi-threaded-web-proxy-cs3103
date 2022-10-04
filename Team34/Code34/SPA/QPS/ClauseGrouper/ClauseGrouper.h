#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../ClauseGroup.h"
#include "../Clause.h"



class ClauseGrouper
{
private:
	std::vector<Clause> clauses_;
	std::vector<std::string> synonyms_;
	std::shared_ptr<ClauseGroup> clauses_wo_syn_;
	std::vector<std::shared_ptr<ClauseGroup>> clauses_wo_select_syn_;
	std::vector<std::shared_ptr<ClauseGroup>> clauses_w_select_syn_;

	ClauseGrouper(std::vector<Clause> clauses, std::vector<std::string> synonyms)
		: clauses_{ clauses }, synonyms_{synonyms} {};


public:
	static std::shared_ptr<ClauseGrouper> CreateClauseGrouper(std::vector<Clause> clauses, std::vector<std::string> synonyms) {
		return std::make_shared<ClauseGrouper>(clauses, synonyms);
	}

	virtual void Group() = 0;

	std::shared_ptr<ClauseGroup> GetClauseGroupWoSyn() {
		return clauses_wo_syn_;
	}
	
	std::vector<std::shared_ptr<ClauseGroup>> GetClauseGroupsWoSelectSyn() {
		return clauses_wo_select_syn_;
	}

	std::vector<std::shared_ptr<ClauseGroup>> GetClauseGroupsWithSelectSyn() {
		return clauses_w_select_syn_;
	}

};

