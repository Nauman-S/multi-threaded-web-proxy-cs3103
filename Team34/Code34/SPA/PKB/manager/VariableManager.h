#pragma once

#include <unordered_set>
#include <string>

class VariableManager
{
public:
    void AddVariable(string var);
    bool IsVariable(string var);
    std::shared_ptr<unordered_set<string>> GetAllVariables();
private:
    static unordered_set<string> variables_;
};