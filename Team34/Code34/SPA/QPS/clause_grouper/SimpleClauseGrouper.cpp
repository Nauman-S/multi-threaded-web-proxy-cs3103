#include "SimpleClauseGrouper.h"

#include "../clause/Clause.h"

using std::vector;
using std::shared_ptr;

void SimpleClauseGrouper::Group() {

	vector<shared_ptr<Clause>> clauses_wo_syn_;

	vector<shared_ptr<Clause>> clauses_wo_select_syn_;

	vector<shared_ptr<Clause>> clauses_w_select_syn;

	for (shared_ptr<Clause> clause : clauses_) {
		if (clause->CountSynonyms() == 0) {
			clauses_wo_syn_.push_back(clause);
			continue;
		}

		//if (AreSelectSynsIn(*(clause->GetSynonyms()))) {
		//	clauses_w_select_syn.push_back(clause);
		//	continue;
		//}

		//clauses_wo_select_syn_.push_back(clause);


		clauses_w_select_syn.push_back(clause);

	}

	group_wo_syn_ = std::make_shared<ClauseGroup>(clauses_wo_syn_);
	groups_wo_select_syn_.clear();
	groups_w_select_syn_.clear();
	groups_wo_select_syn_.push_back(std::make_shared<ClauseGroup>(clauses_wo_select_syn_));
	groups_w_select_syn_.push_back(std::make_shared<ClauseGroup>(clauses_w_select_syn));

}


