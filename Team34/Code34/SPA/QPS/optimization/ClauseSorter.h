#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <string>

#include "PriorityManager.h"
#include "../clause/ClauseGroup.h"
#include "../../Utils/algo/UnionFind.h"

class ClauseSorter {
private:
    void AddClauseToList(std::shared_ptr<Clause> clause, std::vector<std::shared_ptr<Clause>>& optimized_clauses, std::unordered_set<std::string>& used_syns);
    
    bool ContainsUsedSyns(std::shared_ptr<Clause> clause, std::unordered_set<std::string>& used_syns);

public:
    std::shared_ptr<ClauseGroup> SortClausesInGroup(std::shared_ptr<ClauseGroup>);
};

