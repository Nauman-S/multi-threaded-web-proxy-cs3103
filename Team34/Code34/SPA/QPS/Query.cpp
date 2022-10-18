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

shared_ptr<vector<shared_ptr<Clause>>> Query::GetAllClauses() {
	shared_ptr<vector<shared_ptr<Clause>>> clauses = std::make_shared<vector<shared_ptr<Clause>>>();

	shared_ptr<std::vector<shared_ptr<Rel>>> relations = GetRelations();
	shared_ptr<std::vector<shared_ptr<Pattern>>> patterns = GetPatterns();
	shared_ptr<std::vector<shared_ptr<With>>> with_clauses = GetWithClauses();

	clauses->insert(clauses->end(), relations->begin(), relations->end());
	clauses->insert(clauses->end(), patterns->begin(), patterns->end());
	clauses->insert(clauses->end(), with_clauses->begin(), with_clauses->end());

	return clauses;
}