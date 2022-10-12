#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class UnionFind {
private:
	std::vector<std::string> synonyms_;
	std::vector<unsigned> parents_;
	std::unordered_map<std::string, unsigned> syn_to_idx_map_;

	unsigned Find(unsigned idx);

public:
	UnionFind(std::vector<std::string> synonyms);

	void Union(std::string first_syn, std::string second_syn);

	std::string Find(std::string syn);

};