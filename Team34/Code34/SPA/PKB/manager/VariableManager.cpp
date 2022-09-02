#include "VariableManager.h"

void VariableManager::AddVariable(string var)
{
    variables_.insert(var);
}

bool VariableManager::IsVariable(string var)
{
    auto iter = variables_.find(var);
    return iter == variables_.end();
}

std::shared_ptr<unordered_set<string>> VariableManager::GetAllVariables()
{
    return std::make_shared<unordered_set<string>>(variables_);
}