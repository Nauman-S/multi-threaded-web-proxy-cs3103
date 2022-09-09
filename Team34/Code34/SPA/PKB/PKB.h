#pragma once

#include "manager/VariableManager.h"
#include "manager/ConstantManager.h"
#include "manager/ProcedureManager.h"
#include "manager/StatementManager.h"
#include "manager/ParentManager.h"
#include "manager/ModifiesManager.h"
#include "manager/UsesManager.h"
#include "../Utils/type/TypeDef.h"

class PKB
{
public:
	VariableManager variable_manager_;
	ConstantManager constant_manager_;
	ProcedureManager procedure_manager_;
	StatementManager statement_manager_;
	ParentManager parent_manager_;
	ModifiesManager modifies_manager_;
	UsesManager uses_manager_;
};

extern PKB pkb;