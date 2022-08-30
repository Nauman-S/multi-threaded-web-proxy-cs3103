#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <optional>

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::optional;
using std::pair;

class QueryResult
{
protected:
	unordered_map<string, unordered_set<string>&> syn_domains_;

	unordered_map<pair<string, string>, unordered_set<string>&> pr_domains_;

public:
	bool Contains(string syn_name);

	bool Contains(pair<string, string>);

	optional<unordered_set<string>&> GetDomain(string syn_name);

	optional<unordered_set<string>&> GetDomain(pair<string, string>);

	bool InsertToDomain(string syn_name, string value);

	bool InsertToDomain(pair<string, string> pr, string value);

	void SetDomain(string syn_name, unordered_set<string>& domain);

	void SetDomain(pair<string, string> pr, unordered_set<string>& domain);
 };

