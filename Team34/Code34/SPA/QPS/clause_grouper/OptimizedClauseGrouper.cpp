#include "OptimizedClauseGrouper.h"



#include "../Clause.h"
#include "../ClauseGroup.h"
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

	UnionFind union_find = ConstructUnionFind(clauses_w_syn, synonym_set);
	// map a representation to clauses
	unordered_map<string, vector<shared_ptr<Clause>>> rep_to_clauses = ConstructRepToClausesMap(clauses_w_syn, union_find);

	GroupClauseWithSyn(rep_to_clauses);
}

void OptimizedClauseGrouper::GroupClauseWithSyn(std::unordered_map<std::string, std::vector<std::shared_ptr<Clause>>>& rep_to_clauses) {
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

UnionFind OptimizedClauseGrouper::ConstructUnionFind(std::vector<std::shared_ptr<Clause>>& clauses_w_syn, unordered_set<string>& synonym_set) {
	UnionFind union_find(vector<string>(synonym_set.begin(), synonym_set.end()));
	for (shared_ptr<Clause> clause : clauses_w_syn) {
		if (clause->CountSynonyms() < 2) {
			continue;
		}
		shared_ptr<vector<string>> curr_syns = clause->GetSynonyms();
		union_find.Union(curr_syns->at(0), curr_syns->at(1));
	}

	return union_find;
}

std::unordered_map<string, vector<shared_ptr<Clause>>> OptimizedClauseGrouper::ConstructRepToClausesMap(vector<shared_ptr<Clause>>& clauses_w_syn, UnionFind& union_find) {
	unordered_map<string, vector<shared_ptr<Clause>>> rep_to_clauses;
	for (shared_ptr<Clause> clause : clauses_w_syn) {
		shared_ptr<vector<string>> curr_syns = clause->GetSynonyms();

		string representation = union_find.Find(curr_syns->at(0));
		if (rep_to_clauses.count(representation) > 0) {
			rep_to_clauses.at(representation).push_back(clause);
		}
		else {
			rep_to_clauses.insert({ representation, vector<shared_ptr<Clause>>({ clause }) });
		}
	}
	return rep_to_clauses;
}

vector<shared_ptr<Clause>> OptimizedClauseGrouper::OptimizeOrderWithinGroup(vector<shared_ptr<Clause>> clauses) {
	unordered_set<shared_ptr<Clause>> remained_clause_set(clauses.begin(), clauses.end());
	vector<shared_ptr<Clause>> optimized_clauses;
	PriorityManager priority_manager;

	unordered_set<string> used_syns;


	auto priority_compare = [&priority_manager](shared_ptr<Clause> a, shared_ptr<Clause> b) { return a->GetPriority(priority_manager) < b->GetPriority(priority_manager); };
	std::set<shared_ptr<Clause>, decltype(priority_compare)> waiting_clause_set(priority_compare);

	// Step 1: select the clause with highest priority
	shared_ptr<Clause> smallest_clause = clauses.at(0);
	for (shared_ptr<Clause> clause : remained_clause_set) {
		if (clause->GetPriority(priority_manager) < smallest_clause->GetPriority(priority_manager)) {
			smallest_clause = clause;
		}
	}
	remained_clause_set.erase(smallest_clause);
	AddClauseToList(smallest_clause, optimized_clauses, used_syns);
	

	// Step 2: In each iteration, add clause with used synonyms to waiting set,
	//			and add the highest priority clause in waiting set to optimized clauses
	while (remained_clause_set.size() > 0) {
		vector<shared_ptr<Clause>> curr_waiting_clauses = GetWaitingClauses(remained_clause_set, used_syns);
		for (shared_ptr<Clause> clause : curr_waiting_clauses) {
			remained_clause_set.erase(clause);
			waiting_clause_set.insert(clause);
		}
		smallest_clause = *waiting_clause_set.begin();
		waiting_clause_set.erase(smallest_clause);
		AddClauseToList(smallest_clause, optimized_clauses, used_syns);
	}

	// Step 3: keep adding the highest priority clause in waiting set to optimized clauses
	while (waiting_clause_set.size() > 0) {
		smallest_clause = *waiting_clause_set.begin();
		waiting_clause_set.erase(smallest_clause);
		AddClauseToList(smallest_clause, optimized_clauses, used_syns);
	}

	return optimized_clauses;
}

void OptimizedClauseGrouper::AddClauseToList(shared_ptr<Clause> clause, vector<shared_ptr<Clause>>& optimized_clauses, unordered_set<string>& used_syns) {
	optimized_clauses.push_back(clause);
	shared_ptr<vector<string>> synonyms = clause->GetSynonyms();
	used_syns.insert(synonyms->begin(), synonyms->end());
}


vector<shared_ptr<Clause>> OptimizedClauseGrouper::GetWaitingClauses(unordered_set<shared_ptr<Clause>>& remained_clause_set, unordered_set<string>& used_syns) {
	vector<shared_ptr<Clause>> waiting_clauses;
	for (shared_ptr<Clause> clause : remained_clause_set) {
		if (ContainsUsedSyns(clause, used_syns)) {
			waiting_clauses.push_back(clause);
		}
	}
	return waiting_clauses;
}


bool OptimizedClauseGrouper::ContainsUsedSyns(shared_ptr<Clause> clause, unordered_set<string>& used_syns) {
	shared_ptr<vector<string>> syns_in_clause = clause->GetSynonyms();
	for (string& syn : *syns_in_clause) {
		if (used_syns.count(syn) > 0) {
			return true;
		}
	}
	return false;
}
