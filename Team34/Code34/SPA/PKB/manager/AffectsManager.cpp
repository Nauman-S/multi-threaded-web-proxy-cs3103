#include "AffectsManager.h"

#include <stack>

#include "../PKB.h"

bool AffectsManager::CheckAffects(StmtNum cause, StmtNum effect) {
	if (!IsPossibleAffectPair(cause, effect)) {
		return false;
	}

	Variable modified_var = GetModifiedVarInAssign(cause);

	std::unordered_set<StmtNum> visited;
	std::stack<StmtNum> stack;
	stack.push(cause);

	while (!stack.empty()) {
		StmtNum stmt = stack.top();
		stack.pop();

		std::shared_ptr<std::unordered_set<StmtNum>> next_stmts = pkb.next_manager_.GetNextStmtsFromStmt(stmt);
		for (auto child = next_stmts->begin(); child != next_stmts->end(); ++child) {
			if (visited.find(*child) != visited.end()) {
				continue;
			}
			visited.insert(*child);

			if (*child == effect) {
				// We have previously confirmed that this is a possible affects pair,
				// as long as we find the goal, the affect relationship holds
				return true;
			}

			if (IsAffected(modified_var, *child)) {
				// Backtrack once there is a statement that affects the cause statement
				continue;
			}
			stack.push(*child);
		}
	}
	return false;
}

// Check if given two statements fulfill prerequisities for affects
//   1. Both statement must be assignment statements
//   2. Modified var in cause should be used in effect
bool AffectsManager::IsPossibleAffectPair(StmtNum cause, StmtNum effect) {
	if (!IsAssignStmt(cause) || !IsAssignStmt(effect)) {
		return false;
	}

	Variable modified_var = GetModifiedVarInAssign(cause);
	return pkb.uses_manager_.CheckUses(effect, modified_var);
}

// Check whether the variable is modified by an assignment,
// read or procedure call statement
bool AffectsManager::IsAffected(Variable var, StmtNum stmt) {
	if (!IsAssignStmt(stmt) || !IsReadStmt(stmt) || !IsCallStmt(stmt)) {
		return false;
	}

	return pkb.modifies_manager_.CheckModifies(stmt, var);
}

Variable AffectsManager::GetModifiedVarInAssign(StmtNum assign) {
	std::shared_ptr<std::unordered_set<Variable>> vars = pkb.modifies_manager_.GetVarByStmtNum(assign);
	assert(vars->size() == 1 && "Assign statements should modify exactly one variable");
	Variable modified_var = *(vars->begin());
	return modified_var;
}

bool AffectsManager::IsStatementType(StmtNum stmt, RefType type) {
	std::shared_ptr<RefType> cause_type = pkb.statement_manager_.GetStatementType(stmt);
	return *cause_type == type;
}

bool AffectsManager::IsAssignStmt(StmtNum stmt) {
	return IsStatementType(stmt, RefType::kAssignRef);
}

bool AffectsManager::IsReadStmt(StmtNum stmt) {
	return IsStatementType(stmt, RefType::kReadRef);
}

bool AffectsManager::IsCallStmt(StmtNum stmt) {
	return IsStatementType(stmt, RefType::kCallRef);
}
