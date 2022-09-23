#include "CallsManager.h"

void CallsManager::SetCalls(Procedure caller, Procedure callee)
{
	calls_store_.SetRelation(caller, callee);
}

bool CallsManager::CheckCalls(Procedure caller, Procedure callee)
{
	return calls_store_.CheckRelation(caller, callee);
}

bool CallsManager::IsEmpty()
{
	return calls_store_.IsEmpty();
}

std::shared_ptr<std::unordered_set<Procedure>> CallsManager::GetCalleeFromCaller(Procedure caller)
{
	return calls_store_.GetRHSByLHS(caller);
}

std::shared_ptr<std::unordered_set<Procedure>> CallsManager::GetCallerFromCallee(Procedure callee)
{
	return calls_store_.GetLHSByRHS(callee);
}

std::shared_ptr<std::unordered_set<Procedure>> CallsManager::GetAllCallers()
{
	return calls_store_.GetAllLHS();
}

std::shared_ptr<std::unordered_set<Procedure>> CallsManager::GetAllCallees()
{
	return calls_store_.GetAllRHS();
}

std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> CallsManager::GetAllCallsRelations()
{
	return calls_store_.GetAllRelations();
}

void CallsManager::SetCallsT(Procedure caller, Procedure callee)
{
	return calls_store_.SetTransitiveRelation(caller, callee);
}

bool CallsManager::CheckCallsT(Procedure caller, Procedure callee)
{
	return calls_store_.CheckTransitiveRelation(caller, callee);
}

std::shared_ptr<std::unordered_set<Procedure>> CallsManager::GetAllCalleeFromCaller(Procedure caller)
{
	return calls_store_.GetAllTransitiveRHS(caller);
}

std::shared_ptr<std::unordered_set<Procedure>> CallsManager::GetAllCallerFromCallee(Procedure callee)
{
	return calls_store_.GetAllTransitiveLHS(callee);
}

std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> CallsManager::GetAllCallsTRelations()
{
	return calls_store_.GetAllTransitiveRelations();
}
