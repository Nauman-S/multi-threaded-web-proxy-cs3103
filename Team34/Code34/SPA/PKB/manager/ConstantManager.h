#pragma once

#include <unordered_set>

class ConstantManager
{
public:
    void AddConstant(int constant);
    bool IsConstant(int constant);
    std::shared_ptr<unordered_set<int>> GetAllConstants();
private:
    static unordered_set<int> constants_;
};