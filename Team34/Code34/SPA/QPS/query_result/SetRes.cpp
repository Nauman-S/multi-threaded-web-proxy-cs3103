#include "SetRes.h"

using std::string;
using std::unordered_set;
using std::shared_ptr;

bool SetRes::Merge(shared_ptr<SetRes> other) {
	shared_ptr<unordered_set<string>> merged_result = std::make_shared<unordered_set<string>>();
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