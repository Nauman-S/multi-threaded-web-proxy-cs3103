#pragma once

#include <unordered_set>

class ConstantManager
{
public:
    void AddConstant(int constant);
    bool IsConstant(int constant);
    std::unordered_set<int>& GetAllConstants();
private:
    static std::unordered_set<int> constants_;
};