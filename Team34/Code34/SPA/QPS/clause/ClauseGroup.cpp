#include "ClauseGroup.h"

std::shared_ptr<std::unordered_set<std::string>> ClauseGroup::GetSynSet() {
	std::shared_ptr<std::unordered_set<std::string>> syn_set = std::make_shared<std::unordered_set<std::string>>();

	for (std::shared_ptr<Clause> clause : clauses_) {
		std::shared_ptr<std::vector<std::string>> syns = clause->GetSynonyms();
		syn_set->insert(syns->begin(), syns->end());
	}

	return syn_set;
}
 