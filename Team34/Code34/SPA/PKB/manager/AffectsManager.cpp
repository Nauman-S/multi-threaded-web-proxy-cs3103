#include "AffectsManager.h"

#include <queue>

#include "../PKB.h"

bool AffectsManager::CheckAffects(StmtNum cause, StmtNum effect) {
	if (!IsPossibleAffectPair(cause, effect)) {
		return false;
	}
	Variable& modified_var = GetModifiedVarInAssign(cause);
	std::unordered_set<StmtNum> visited;
	std::queue<StmtNum> queue;
	queue.push(cause);
	while (!queue.empty()) {
		StmtNum stmt = queue.front();
		queue.pop();
		std::shared_ptr<std::unordered_set<StmtNum>> next_stmts = pkb.next_manager_.GetNextStmtsFromStmt(stmt);
		for (auto child = next_stmts->begin(); child != next_stmts->end(); ++child) {
			if (visited.find(*child) != visited.end())
			{
				continue;
			}
			if (*child == effect)
			{
				// We have previously confirmed that this is a possible affects pair,
				// as long as we find the goal, the affect relationship holds
				return true;
			}
			if (!IsDirectlyModified(modified_var, *child))
			{
				visited.insert(*child);
				queue.push(*child);
			}
		}
	}
	return false;
}

bool AffectsManager::IsEmpty()
{
	// TODO
	return false;
}

std::shared_ptr<std::unordered_set<StmtNum>> AffectsManager::GetEffectStmtsFromStmt(StmtNum stmt)
{
	// TODO: Check that stmt is assign stmt
	std::shared_ptr<std::unordered_set<StmtNum>> effect_stmts = std::make_shared<std::unordered_set<StmtNum>>();
	Variable& modified_var = GetModifiedVarInAssign(stmt);
	std::unordered_set<StmtNum> visited;
	std::queue<StmtNum> queue;
	queue.push(stmt);
	while (!queue.empty())
	{
		StmtNum stmt = queue.front();
		queue.pop();
		std::shared_ptr<std::unordered_set<StmtNum>> next_stmts = pkb.next_manager_.GetNextStmtsFromStmt(stmt);
		for (auto child = next_stmts->begin(); child != next_stmts->end(); ++child)
		{
			if (visited.find(*child) != visited.end())
			{
				continue;
			}
			if (IsAssignStatementUsingVariable(modified_var, *child))
			{
				effect_stmts->insert(*child);
			}
			else if (!IsDirectlyModified(modified_var, *child))
			{
				visited.insert(*child);
				queue.push(*child);
			}
		}
	}
	return effect_stmts;
}

std::shared_ptr<std::unordered_set<StmtNum>> AffectsManager::GetCauseStmtsFromStmt(StmtNum stmt)
{
	// TODO: Check that stmt is assign stmt
	std::shared_ptr<std::unordered_set<StmtNum>> cause_stmts = std::make_shared<std::unordered_set<StmtNum>>();
	std::shared_ptr <std::unordered_set<Variable>> used_var = pkb.uses_manager_.GetVarByStmtNum(stmt);
	for (auto var = used_var->begin(); var != used_var->end(); ++var)
	{
		std::unordered_set<StmtNum> visited;
		std::queue<StmtNum> queue;
		queue.push(stmt);
		while (!queue.empty())
		{
			StmtNum stmt = queue.front();
			queue.pop();
			std::shared_ptr<std::unordered_set<StmtNum>> prev_stmts = pkb.next_manager_.GetPrevStmtsFromStmt(stmt);
			for (auto parent = prev_stmts->begin(); parent != prev_stmts->end(); ++parent)
			{
				if (visited.find(*parent) != visited.end())
				{
					continue;
				}
				if (IsAssignStatementModifyingVariable(*var, *parent))
				{
					cause_stmts->insert(*parent);
				}
				else if (!IsDirectlyModified(*var, *parent))
				{
					visited.insert(*parent);
					queue.push(*parent);
				}
			}
		}
	}
	return cause_stmts;
}

std::shared_ptr<std::unordered_set<StmtNum>> AffectsManager::GetAllEffectStmts()
{
	// TODO: get all stmts that modify and BFS to find all stmts that Uses the same variable
	return std::shared_ptr<std::unordered_set<StmtNum>>();
}

std::shared_ptr<std::unordered_set<StmtNum>> AffectsManager::GetAllCauseStmts()
{
	// TODO: get all stmts that uses and reverse BFS to find all stmts that Modifies the same variable
	return std::shared_ptr<std::unordered_set<StmtNum>>();
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> AffectsManager::GetAllAffectsRelations()
{
	// TODO: discuss implementation
	return std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>>();
}

// APIs related to Affects* relation
bool AffectsManager::CheckAffectsT(StmtNum cause, StmtNum effect)
{
	std::shared_ptr<std::unordered_set<Variable>> modified_vars = pkb.modifies_manager_.GetVarByStmtNum(cause);
	std::shared_ptr<std::unordered_set<Variable>> uses_vars = pkb.uses_manager_.GetVarByStmtNum(effect);
	for (auto iter = modified_vars->begin(); iter != modified_vars->end(); ++iter)
	{
		if (uses_vars->find(*iter) != uses_vars->end())
		{
			if (pkb.next_manager_.CheckNextT(cause, effect))
			{
				return true;
			}
		}
	}
	return false;
}

std::shared_ptr<std::unordered_set<StmtNum>> AffectsManager::GetAllEffectStmtsFromStmt(StmtNum stmt)
{
	// TODO: get all stmts that modify and BFS to find all stmts that Uses the same variable
	return std::shared_ptr<std::unordered_set<StmtNum>>();
}

std::shared_ptr<std::unordered_set<StmtNum>> AffectsManager::GetAllCauseStmtsFromStmt(StmtNum stmt)
{
	// TODO: get all stmts that uses and reverse BFS to find all stmts that Modifies the same variable
	return std::shared_ptr<std::unordered_set<StmtNum>>();
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> AffectsManager::GetAllAffectsTRelations()
{
	// TODO: discuss implementation
	return std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>>();
}

// Helper functions

// Check if given two statements fulfill prerequisities for affects
//   1. Both statement must be assignment statements
//   2. Modified var in cause should be used in effect
bool AffectsManager::IsPossibleAffectPair(StmtNum cause, StmtNum effect)
{
	if (!IsAssignStmt(cause) || !IsAssignStmt(effect))
	{
		return false;
	}

	Variable modified_var = GetModifiedVarInAssign(cause);
	return pkb.uses_manager_.CheckUses(effect, modified_var);
}

// Check whether the variable is directly modified by an assignment,
// read or procedure call statement
bool AffectsManager::IsDirectlyModified(Variable var, StmtNum stmt)
{
	if (!IsAssignStmt(stmt) || !IsReadStmt(stmt) || !IsCallStmt(stmt))
	{
		return false;
	}

	return pkb.modifies_manager_.CheckModifies(stmt, var);
}

bool AffectsManager::IsAssignStatementModifyingVariable(Variable var, StmtNum stmt)
{
	return IsAssignStmt(stmt) && pkb.modifies_manager_.CheckModifies(stmt, var);
}

bool AffectsManager::IsAssignStatementUsingVariable(Variable var, StmtNum stmt)
{
	return IsAssignStmt(stmt) && pkb.uses_manager_.CheckUses(stmt, var);
}

Variable AffectsManager::GetModifiedVarInAssign(StmtNum assign)
{
	std::shared_ptr<std::unordered_set<Variable>> vars = pkb.modifies_manager_.GetVarByStmtNum(assign);
	assert(vars->size() == 1 && "Assign statements should modify exactly one variable");
	Variable modified_var = *(vars->begin());
	return modified_var;
}

bool AffectsManager::IsStatementType(StmtNum stmt, RefType type)
{
	std::shared_ptr<RefType> cause_type = pkb.statement_manager_.GetStatementType(stmt);
	return *cause_type == type;
}

bool AffectsManager::IsAssignStmt(StmtNum stmt)
{
	return IsStatementType(stmt, RefType::kAssignRef);
}

bool AffectsManager::IsReadStmt(StmtNum stmt)
{
	return IsStatementType(stmt, RefType::kReadRef);
}

bool AffectsManager::IsCallStmt(StmtNum stmt)
{
	return IsStatementType(stmt, RefType::kCallRef);
}
