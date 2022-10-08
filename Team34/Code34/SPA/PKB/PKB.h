#pragma once

#include "manager/VariableManager.h"
#include "manager/ConstantManager.h"
#include "manager/ProcedureManager.h"
#include "manager/StatementManager.h"
#include "manager/ParentManager.h"
#include "manager/FollowsManager.h"
#include "manager/ModifiesManager.h"
#include "manager/UsesManager.h"
#include "manager/CallsManager.h"
#include "manager/NextManager.h"
#include "manager/AffectsManager.h"
#include "manager/AssignPatternManager.h"
#include "manager/IfPatternManager.h"
#include "manager/WhilePatternManager.h"

class PKB {
public:
	VariableManager variable_manager_;
	ConstantManager constant_manager_;
	ProcedureManager procedure_manager_;
	StatementManager statement_manager_;
	ParentManager parent_manager_;
	FollowsManager follows_manager_;
	ModifiesManager modifies_manager_;
	UsesManager uses_manager_;
	CallsManager calls_manager_;
	NextManager next_manager_;
	AffectsManager affects_manager_;
	AssignPatternManager assign_pattern_manager_;
	IfPatternManager if_pattern_manager_;
	WhilePatternManager while_pattern_manager_;
};

extern PKB pkb;