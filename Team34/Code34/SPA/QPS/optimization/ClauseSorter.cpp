#include "ClauseSorter.h"

#include <algorithm>
#include <string>

using std::string;
using std::vector;
using std::shared_ptr;
using std::unordered_set;
using std::unordered_map;

shared_ptr<ClauseGroup> ClauseSorter::SortClausesInGroup(shared_ptr<ClauseGroup> clause_group) {
    auto clauses = clause_group->GetClauses();
    if (clauses.size() == 0) {
        return clause_group;
    }

    PriorityManager priority_manager;
    auto priority_comparator = [&priority_manager](shared_ptr<Clause> a, shared_ptr<Clause> b) { return a->GetPriority(priority_manager) < b->GetPriority(priority_manager); };
    std::sort(clauses.begin(), clauses.end(), priority_comparator);

    vector<shared_ptr<Clause>> optimized_clauses;
    unordered_set<string> used_syns;

    size_t num_of_clauses = clauses.size();
    vector<bool> is_clause_used(num_of_clauses, false);
    vector<bool> can_clause_be_used(num_of_clauses, false);
    can_clause_be_used[0] = true;

    shared_ptr<Clause> smallest_clause;
    for (size_t count = 0; count < num_of_clauses; ++count) {
        for (size_t idx = 0; idx < num_of_clauses; ++idx) {
            if (!is_clause_used[idx] && can_clause_be_used[idx]) {
                smallest_clause = clauses[idx];
                is_clause_used[idx] = true;
                break;
            }
        }

        AddClauseToList(smallest_clause, optimized_clauses, used_syns);
        for (unsigned idx = 0; idx < clauses.size(); ++idx) {
            if (is_clause_used[idx]) {
                continue;
            }
            shared_ptr<Clause> clause = clauses[idx];
            if (ContainsUsedSyns(clause, used_syns)) {
                can_clause_be_used[idx] = true;
            }
        }
    }
    return std::make_shared<ClauseGroup>(optimized_clauses);
}

void ClauseSorter::AddClauseToList(shared_ptr<Clause> clause, vector<shared_ptr<Clause>>& optimized_clauses, unordered_set<string>& used_syns) {
    optimized_clauses.push_back(clause);
    shared_ptr<vector<string>> synonyms = clause->GetSynonyms();
    used_syns.insert(synonyms->begin(), synonyms->end());
}

bool ClauseSorter::ContainsUsedSyns(shared_ptr<Clause> clause, unordered_set<string>& used_syns) {
    shared_ptr<vector<string>> syns_in_clause = clause->GetSynonyms();
    for (string& syn : *syns_in_clause) {
        if (used_syns.count(syn) > 0) {
            return true;
        }
    }
    return false;
}
