#include "UnionFind.h"

UnionFind::UnionFind(std::vector<std::string> synonyms) {
    unsigned size = synonyms.size();
    synonyms_ = synonyms;
    parents_ = std::vector<unsigned>(size);
    for (unsigned i = 0; i < size; i++) {
        parents_[i] = i;
        syn_to_idx_map_.insert({ synonyms[i], i });
    }
}

void UnionFind::Union(std::string first_syn, std::string second_syn) {
    unsigned first_idx = syn_to_idx_map_.at(first_syn);
    unsigned second_idx = syn_to_idx_map_.at(second_syn);

    unsigned first_representation = Find(first_idx);
    unsigned second_representation = Find(second_idx);

    parents_[second_representation] = first_representation;
}

unsigned UnionFind::Find(unsigned idx) {
    if (idx == parents_[idx]) {
        return idx;
    }
    // path compression
    parents_[idx] = Find(parents_[idx]);

    return parents_[idx];
}

std::string UnionFind::Find(std::string syn) {
    unsigned representation = Find(syn_to_idx_map_.at(syn));
    return synonyms_[representation];
}
