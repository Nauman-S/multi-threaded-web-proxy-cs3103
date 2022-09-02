#pragma once
#include <string>
#include <unordered_set>
#include <memory>

using std::string;
using std::unordered_set;

class SetRes
{
protected:
	string syn_;
	unordered_set<string> domain_;

public:
	SetRes(string s, unordered_set<string> d) : syn_{ s }, domain_(d) {};

	string GetSyn() { return syn_; }

	unordered_set<string>& GetDomain() { return domain_; }

	bool Merge(std::shared_ptr<SetRes> other);
};
 
