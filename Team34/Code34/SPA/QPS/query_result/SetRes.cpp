#include "SetRes.h"


bool SetRes::Merge(std::shared_ptr<SetRes> other) {
	unordered_set<string> merged_result = unordered_set<string>();
	for (const string& s : *(other->GetDomain())) {
		if (domain_.count(s)) {
			merged_result.insert(s);
		}
	}
	domain_ = merged_result;

	if (merged_result.size() == 0) {
		return false;
	}
	else {
		return true;
	}

};