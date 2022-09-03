#include "VariableManager.h"

void VariableManager::AddVariable(std::string var)
{
    variables_.insert(var);
}

bool VariableManager::IsVariable(std::string var)
{
    auto iter = variables_.find(var);
    return iter == variables_.end();
}

const std::unordered_set<std::string>& VariableManager::GetAllVariables()
{
    return std::make_shared<unordered_set<string>>(variables_);
}