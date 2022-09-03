#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "EntityManager.h"
#include "../../Utils/type/TypeDef.h"

class ConstantManager : public EntityManager<Constant>
{
};