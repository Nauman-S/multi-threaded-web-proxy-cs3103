#include "StatementManager.h"

void StatementManager::AddStatement(StmtNum stmt_num, RefType type) {
	statement_store_.SetRelation(stmt_num, type);
	statements_.insert(stmt_num);
}

void StatementManager::AddCallsStatement(Procedure proc, StmtNum stmt_num) {
	calls_statements_[proc].insert(stmt_num);
	calls_procedures_[stmt_num] = proc;
}

void StatementManager::AddPrintStatement(Variable var, StmtNum stmt_num) {
	print_statements_[var].insert(stmt_num);
	print_variables_[stmt_num] = var;
}

void StatementManager::AddReadStatement(Variable var, StmtNum stmt_num) {
	read_statements_[var].insert(stmt_num);
	read_variables_[stmt_num] = var;
}

std::shared_ptr<RefType> StatementManager::GetStatementType(StmtNum stmt_num) {
	return statement_store_.GetOne(stmt_num);
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetStatementsByType(RefType type) {
	return statement_store_.GetMany(type);
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetAllStatements() {
	return std::make_shared<std::unordered_set<StmtNum>>(statements_);
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetCallsStatementFromProcedure(Procedure proc) {
	if (calls_statements_.find(proc) == calls_statements_.end()) {
		return std::make_shared<std::unordered_set<StmtNum>>();
	}
	else {
		return std::make_shared<std::unordered_set<StmtNum>>(calls_statements_[proc]);
	}
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetPrintStatementFromVariable(Variable var) {
	if (print_statements_.find(var) == print_statements_.end()) {
		return std::make_shared<std::unordered_set<StmtNum>>();
	}
	else {
		return std::make_shared<std::unordered_set<StmtNum>>(print_statements_[var]);
	}
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetReadStatementFromVariable(Variable var) {
	if (read_statements_.find(var) == read_statements_.end()) {
		return std::make_shared<std::unordered_set<StmtNum>>();
	}
	else {
		return std::make_shared<std::unordered_set<StmtNum>>(read_statements_[var]);
	}
}

std::shared_ptr<Procedure> StatementManager::GetCallsProcedureFromStatement(StmtNum stmt_num) {
	return std::make_shared<Procedure>(calls_procedures_[stmt_num]);
}

std::shared_ptr<Variable> StatementManager::GetPrintVariableFromStatement(StmtNum stmt_num) {
	return std::make_shared<Variable>(print_variables_[stmt_num]);
}

std::shared_ptr<Variable> StatementManager::GetReadVariableFromStatement(StmtNum stmt_num) {
	return std::make_shared<Variable>(read_variables_[stmt_num]);
}

std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Procedure>>>> StatementManager::GetAllCallsStatementProcedurePairs() {
	return GenerateStatementProcedurePairs(calls_procedures_);
}

std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Variable>>>> StatementManager::GetAllPrintStatementVariablePairs() {
	return GenerateStatementVariablePairs(print_variables_);
}
std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Variable>>>> StatementManager::GetAllReadStatementVariablePairs() {
	return GenerateStatementVariablePairs(read_variables_);
}

void StatementManager::Clear() {
	statement_store_.Clear();
	statements_.clear();
	calls_statements_.clear();
	calls_procedures_.clear();
	print_statements_.clear();
	print_variables_.clear();
	read_statements_.clear();
	read_variables_.clear();
}

std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Procedure>>>> StatementManager::GenerateStatementProcedurePairs(std::unordered_map<StmtNum, Procedure>& map) {
	std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Procedure>>>> pairs = std::make_shared<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Procedure>>>>();
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		pairs->push_back(std::make_pair(std::make_shared<StmtNum>(iter->first), std::make_shared<Procedure>(iter->second)));
	}
	return pairs;
}

std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Variable>>>> StatementManager::GenerateStatementVariablePairs(std::unordered_map<StmtNum, Variable>& map) {
	std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Variable>>>> pairs = std::make_shared<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Variable>>>>();
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		pairs->push_back(std::make_pair(std::make_shared<StmtNum>(iter->first), std::make_shared<Variable>(iter->second)));
	}
	return pairs;
}
