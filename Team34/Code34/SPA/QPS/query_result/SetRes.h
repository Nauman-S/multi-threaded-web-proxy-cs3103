#pragma once

#include <string>
#include <unordered_set>
#include <memory>

class SetRes {
protected:
    std::string syn_;
    std::shared_ptr<std::unordered_set<std::string>> domain_ptr_;

public:
    SetRes(std::string s, std::shared_ptr<std::unordered_set<std::string>> d) : syn_{ s }, domain_ptr_(d) {}

    std::string GetSyn() { return syn_; }

    std::shared_ptr<std::unordered_set<std::string>> GetDomain() { return domain_ptr_; }

    bool Merge(std::shared_ptr<SetRes> other);

    bool IsEmpty() { return domain_ptr_->empty(); }
};

