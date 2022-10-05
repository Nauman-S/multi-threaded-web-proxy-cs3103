#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../store/ManyToManyRelation/CallsRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class CallsManager
{
public:
	// Calls Relation methods
	void SetCalls(Procedure caller, Procedure callee);
	bool CheckCalls(Procedure caller, Procedure callee);
	bool IsEmpty();
	std::shared_ptr<std::unordered_set<Procedure>> GetCalleeFromCaller(Procedure caller);
	std::shared_ptr<std::unordered_set<Procedure>> GetCallerFromCallee(Procedure callee);
	std::shared_ptr<std::unordered_set<Procedure>> GetAllCallers();
	std::shared_ptr<std::unordered_set<Procedure>> GetAllCallees();
	std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> GetAllCallsRelations();

	// Calls* Relation methods
	void SetCallsT(Procedure caller, Procedure callee);
	bool CheckCallsT(Procedure caller, Procedure callee);
	std::shared_ptr<std::unordered_set<Procedure>> GetAllCalleeFromCaller(Procedure caller);
	std::shared_ptr<std::unordered_set<Procedure>> GetAllCallerFromCallee(Procedure callee);
	std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> GetAllCallsTRelations();
private:
	CallsRelationStore calls_store_;
};