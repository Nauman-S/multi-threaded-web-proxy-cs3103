#include "Query.h"

#include <string>

using std::string;


vector<string> Query::GetSelectSynonyms() {
	vector<string> synonyms;
	for (shared_ptr<Ref> ref : *select_tuple_) {
		synonyms.push_back(ref->GetName());
	}
	return synonyms;
}