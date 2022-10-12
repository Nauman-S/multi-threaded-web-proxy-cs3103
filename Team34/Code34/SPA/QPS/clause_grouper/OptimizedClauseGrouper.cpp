#include "OptimizedClauseGrouper.h"

#include <unordered_set>


#include "../Clause.h"
#include "../ClauseGroup.h"
#include "../../Utils/algo/UnionFind.h"
#include "../PriorityManager.h"


using std::string;
using std::vector;
using std::shared_ptr;
using std::unordered_set;
using std::unordered_map;

void OptimizedClauseGrouper::Group() {
	vector<shared_ptr<Clause>> clauses_wo_syn;
	vector<shared_ptr<Clause>> clauses_w_syn;
	unordered_set<string> synonym_set;


	for (shared_ptr<Clause> clause : clauses_) {
		if (clause->CountSynonyms() == 0) {
			clauses_wo_syn.push_back(clause);
			continue;
		} 
		clauses_w_syn.push_back(clause);
		shared_ptr<vector<string>> curr_syns = clause->GetSynonyms();

		synonym_set.insert(curr_syns->begin(), curr_syns->end());
	}
	group_wo_syn_ = std::make_shared<ClauseGroup>(clauses_wo_syn);
	


	UnionFind union_find(vector<string>(synonym_set.begin(), synonym_set.end()));
	for (shared_ptr<Clause> clause : clauses_w_syn) {
		if (clause->CountSynonyms() < 2) {
			continue;
		}
		shared_ptr<vector<string>> curr_syns = clause->GetSynonyms();
		union_find.Union(curr_syns->at(0), curr_syns->at(1));
	}


	// map a representation to clauses
	unordered_map<string, vector<shared_ptr<Clause>>> rep_to_clauses;
	for (shared_ptr<Clause> clause : clauses_w_syn) {
		shared_ptr<vector<string>> curr_syns = clause->GetSynonyms();

		string representation = union_find.Find(curr_syns->at(0));
		if (rep_to_clauses.count(representation) > 0) {
			rep_to_clauses.at(representation).push_back(clause);
		}
		else {
			rep_to_clauses.insert({ representation, vector<shared_ptr<Clause>>({ clause })});
		}
	}


	for (auto& iterator = rep_to_clauses.begin(); iterator != rep_to_clauses.end(); ++iterator) {
		vector<shared_ptr<Clause>> optimized_clauses = OptimizeOrderWithinGroup(iterator->second);
		shared_ptr<ClauseGroup> optimized_clause_group = std::make_shared<ClauseGroup>(optimized_clauses);
		shared_ptr<unordered_set<string>> syns_in_group = optimized_clause_group->GetSynSet();

		bool contains_select_syn = false;

		for (string& select_syn : select_synonyms_) {
			if (syns_in_group->count(select_syn) > 0) {
				contains_select_syn = true;
				break;
			}
		}

		if (contains_select_syn) {
			groups_w_select_syn_.push_back(optimized_clause_group);
		}
		else {
			groups_wo_select_syn_.push_back(optimized_clause_group);
		}

	}
}

vector<shared_ptr<Clause>> OptimizedClauseGrouper::OptimizeOrderWithinGroup(vector<shared_ptr<Clause>> clauses) {
	unordered_set<shared_ptr<Clause>> origin_clause_set(clauses.begin(), clauses.end());
	vector<shared_ptr<Clause>> optimized_clauses;
	PriorityManager priority_manager;

	unordered_set<string> used_syns;

	shared_ptr<Clause> smallest_clause = clauses.at(0);

	for (shared_ptr<Clause> clause : origin_clause_set) {
		if (clause->GetPriority(priority_manager) < smallest_clause->GetPriority(priority_manager)) {
			smallest_clause = clause;
		}
	}
	optimized_clauses.push_back(smallest_clause);
	origin_clause_set.erase(smallest_clause);
	auto synonyms = smallest_clause->GetSynonyms();
	used_syns.insert(synonyms->begin(),
		synonyms->end());


	auto priority_compare = [&priority_manager](shared_ptr<Clause> a, shared_ptr<Clause> b) { return a->GetPriority(priority_manager) < b->GetPriority(priority_manager); };
	std::set<shared_ptr<Clause>, decltype(priority_compare)> waiting_clauses(priority_compare);
	
	while (origin_clause_set.size() > 0) {
		vector<shared_ptr<Clause>> added_clauses;
		for (shared_ptr<Clause> clause : origin_clause_set) {
			shared_ptr<vector<string>> syns_in_clause = clause->GetSynonyms();
			for (string& syn : *syns_in_clause) {
				if (used_syns.count(syn) > 0) {
					added_clauses.push_back(clause);
					break;
				}
			}
		}

		for (shared_ptr<Clause> clause : added_clauses) {
			origin_clause_set.erase(clause);
			waiting_clauses.insert(clause);
		}

		
		smallest_clause = *waiting_clauses.begin();
		waiting_clauses.erase(smallest_clause);
		optimized_clauses.push_back(smallest_clause);
		synonyms = smallest_clause->GetSynonyms();
		used_syns.insert(synonyms->begin(),
			synonyms->end());
	}

	while (waiting_clauses.size() > 0) {
		// TODO: replicated code, need to refactor£»
		smallest_clause = *waiting_clauses.begin();
		waiting_clauses.erase(smallest_clause);
		optimized_clauses.push_back(smallest_clause);
	}

	return optimized_clauses;
}