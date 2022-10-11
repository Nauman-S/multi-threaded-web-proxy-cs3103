#include "OptimizedClauseGrouper.h"

#include <unordered_set>

#include "../Clause.h"
#include "../ClauseGroup.h"
#include "../../Utils/algo/UnionFind.h"

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
		vector<shared_ptr<Clause>> optimized_clauses = iterator->second;
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