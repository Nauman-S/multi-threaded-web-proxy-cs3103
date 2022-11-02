#pragma once

#include <vector>
#include <memory>
#include <string>
#include <set>

#include "../../clause/ClauseGroup.h"
#include "../../clause/Clause.h"

class ClauseGrouper {
protected:
    std::vector<std::shared_ptr<Clause>> clauses_;
    std::vector<std::string> select_synonyms_;
    std::shared_ptr<ClauseGroup> group_wo_syn_;
    std::vector<std::shared_ptr<ClauseGroup>> groups_wo_select_syn_;
    std::vector<std::shared_ptr<ClauseGroup>> groups_w_select_syn_;

    virtual void Group() = 0;
    bool AreSelectSynsIn(std::vector<std::string> syns);

public:
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
