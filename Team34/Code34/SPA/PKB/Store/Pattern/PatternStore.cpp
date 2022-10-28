#include "PatternStore.h"

void PatternStore::AddPattern(StmtNum stmt_num, Variable var) {
	if (var_to_stmt_map_[var].find(stmt_num) != var_to_stmt_map_[var].end()) {
		return;
	}
	all_statements_.insert(stmt_num);
	all_sv_pairs_.push_back(std::make_pair(stmt_num, var));
	var_to_stmt_map_[var].insert(stmt_num);
}

std::shared_ptr<std::unordered_set<StmtNum>> PatternStore::GetAllStatmentsFromVar(Variable var) {
	if (var_to_stmt_map_.find(var) == var_to_stmt_map_.end()) {
		return std::make_shared<std::unordered_set<StmtNum>>();
	} else {
		return std::make_shared<std::unordered_set<StmtNum>>(var_to_stmt_map_[var]);
	}
}

std::shared_ptr<std::unordered_set<StmtNum>> PatternStore::GetAllStatements() {
	return std::make_shared<std::unordered_set<StmtNum>>(all_statements_);
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> PatternStore::GetAllPatterns() {
	return std::make_shared<std::vector<std::pair<StmtNum, Variable>>>(all_sv_pairs_);
}

void PatternStore::Clear() {
	var_to_stmt_map_.clear();
	all_statements_.clear();
	all_sv_pairs_.clear();
}
