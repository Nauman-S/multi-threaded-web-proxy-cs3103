#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <optional>

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::optional;

class QueryResult
{
protected:
	unordered_map<string, unordered_set<string>&> domains_;

public:
	bool Contains(string syn_name);

	const optional<unordered_set<string>&> GetDomain(string syn_name);

	bool InsertToDomain(string syn_name, string value);

	void SetDomain(string syn_name, unordered_set<string>& domain);
 };

