#include "ClauseGrouper.h"

bool ClauseGrouper::AreSelectSynsIn(std::vector<std::string> syns) {
	for (std::string select_syn : select_synonyms_) {
		if (std::find(syns.begin(), syns.end(), select_syn) != syns.end()) {
			return true;
		}
	}
	return false;
}