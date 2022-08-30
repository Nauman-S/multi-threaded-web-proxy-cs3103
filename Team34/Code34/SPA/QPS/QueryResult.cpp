#include "QueryResult.h"

bool QueryResult::Contains(string syn_name)
{
	return domains_.find(syn_name) != domains_.end();
}

const optional<unordered_set<string>&> QueryResult::GetDomain(string syn_name)
{
	if (auto pair=domains_.find(syn_name); pair!=domains_.end()) {
		return optional(pair->second);
	}
	else {
		return optional<unordered_set<string>&>();
	}
}

bool QueryResult::InsertToDomain(string syn_name, string value)
{
	if (auto pair = domains_.find(syn_name); pair != domains_.end()) {
		auto [iter, ok] = pair->second.insert(value);
		return ok;
	}
	else {
		return false;
	}
}

void QueryResult::SetDomain(string syn_name, unordered_set<string>& domain)
{
	domains_.insert_or_assign(syn_name, domain);
}
