#pragma once

#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "ClauseGrouper.h"
#include "../../../Utils/algo/UnionFind.h"

class OptimizedClauseGrouper :
    public ClauseGrouper {
private:
    UnionFind ConstructUnionFind(std::vector<std::shared_ptr<Clause>>& clauses_w_syn, std::unordered_set<std::string>& synonym_set);
    std::unordered_map<std::string, std::vector<std::shared_ptr<Clause>>> ConstructRepToClausesMap(std::vector<std::shared_ptr<Clause>>& clauses_w_syn, UnionFind& union_find);

    void GroupClauseWithSyn(std::unordered_map<std::string, std::vector<std::shared_ptr<Clause>>>& rep_to_clauses);

protected:
    void Group() override;
public:
    OptimizedClauseGrouper(std::vector<std::shared_ptr<Clause>> clauses, std::vector<std::string> synonyms)
        :ClauseGrouper{ clauses, synonyms } {
        Group();
    }

};