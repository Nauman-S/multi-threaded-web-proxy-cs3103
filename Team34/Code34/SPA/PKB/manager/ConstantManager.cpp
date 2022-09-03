#include "ConstantManager.h"

void ConstantManager::AddConstant(int constant)
{
    constants_.insert(constant);
}

bool ConstantManager::IsConstant(int constant)
{
    auto iter = constants_.find(constant);
    return iter == constants_.end();
}

std::unordered_set<int>& ConstantManager::GetAllConstants()
{
    return std::make_shared<unordered_set<int>>(constants_);
}