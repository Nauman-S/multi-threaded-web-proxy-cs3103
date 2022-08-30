#include "QueryResult.h"

bool QueryResult::Contains(string syn_name)
{
	return syn_domains_.find(syn_name) != syn_domains_.end();
}

bool QueryResult::Contains(pair<string, string> pr)
{
	return pr_domains_.find(pr) != pr_domains_.end();
}

optional<unordered_set<string>&> QueryResult::GetDomain(string syn_name)
{
	if (auto pair=syn_domains_.find(syn_name); pair!=syn_domains_.end()) {
		return optional(pair->second);
	}
	else {
		return optional<unordered_set<string>&>();
	}
}

optional<unordered_set<string>&> QueryResult::GetDomain(pair<string, string> pr)
{
	if (auto pair = pr_domains_.find(pr); pair != pr_domains_.end()) {
		return optional(pair->second);
	}
	else {
		return optional<unordered_set<string>&>();
	}
}

bool QueryResult::InsertToDomain(string syn_name, string value)
{
	if (auto pair = syn_domains_.find(syn_name); pair != syn_domains_.end()) {
		auto [iter, ok] = pair->second.insert(value);
		return ok;
	}
	else {
		return false;
	}
}

bool QueryResult::InsertToDomain(pair<string, string> pr, string value)
{
	if (auto pair = pr_domains_.find(pr); pair != pr_domains_.end()) {
		auto [iter, ok] = pair->second.insert(value);
		return ok;
	}
	else {
		return false;
	}
}

void QueryResult::SetDomain(string syn_name, unordered_set<string>& domain)
{
	syn_domains_.insert_or_assign(syn_name, domain);
}

void QueryResult::SetDomain(pair<string, string> pr, unordered_set<string>& domain)
{
	pr_domains_.insert_or_assign(pr, domain);
}
