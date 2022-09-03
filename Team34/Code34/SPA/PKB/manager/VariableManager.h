#pragma once

#include <unordered_set>

class VariableManager
{
public:
    void AddVariable(std::string var);
    bool IsVariable(std::string var);
    std::unordered_set<std::string>& GetAllVariables();
private:
    static std::unordered_set<std::string> variables_;
};