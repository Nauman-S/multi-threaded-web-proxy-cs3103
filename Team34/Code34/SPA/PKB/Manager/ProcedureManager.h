#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "../store/Entity/EntityStore.h"
#include "../../Utils/type/TypeDef.h"

class ProcedureManager: public EntityStore<Procedure> {
};