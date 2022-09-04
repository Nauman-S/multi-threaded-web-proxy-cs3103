#include "SetRes.h"


bool SetRes::Merge(std::shared_ptr<SetRes> other) {
	shared_ptr<unordered_set<string>> merged_result;
	for (const string& s : *(other->GetDomain())) {
		if (domain_ptr_->count(s)) {
			merged_result->insert(s);
		}
	}
	domain_ptr_ = merged_result;

	if (merged_result->size() == 0) {
		return false;
	}
	else {
		return true;
	}
};