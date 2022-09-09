#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "../store/EntityStore.h"
#include "../../Utils/type/TypeDef.h"

class ProcedureManager: public EntityStore<Procedure>
{
};