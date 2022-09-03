#pragma once
#include <string>
#include <unordered_set>
#include <memory>

using std::string;
using std::unordered_set;
using std::shared_ptr;

class SetRes
{
protected:
	string syn_;
	unordered_set<string> domain_;

public:
	SetRes(string s, unordered_set<string> d) : syn_{ s }, domain_(d) {};

	string GetSyn() { return syn_; }

	shared_ptr<unordered_set<string>> GetDomain() { return shared_ptr<unordered_set<string>>(&domain_); }

	bool Merge(std::shared_ptr<SetRes> other);
};
 
