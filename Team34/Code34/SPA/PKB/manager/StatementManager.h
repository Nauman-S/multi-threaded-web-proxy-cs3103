#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "../../Utils/type/RefType.h"
#include "../../Utils/type/TypeDef.h"
#include "../../PKB/store/ManyToOneRelation/ManyToOneRelationStore.h"

class StatementManager
{
public:
	void AddStatement(StmtNum stmt_num, RefType type);
	void AddCallsStatement(Procedure proc, StmtNum stmt_num);
	void AddPrintStatement(Variable var, StmtNum stmt_num);
	void AddReadStatement(Variable var, StmtNum stmt_num);
	std::shared_ptr<RefType> GetStatementType(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<StmtNum>> GetStatementsByType(RefType type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();
	std::shared_ptr<std::unordered_set<StmtNum>> GetCallsStatementFromProcedure(Procedure proc);
	std::shared_ptr<std::unordered_set<StmtNum>> GetPrintStatementFromVariable(Variable var);
	std::shared_ptr<std::unordered_set<StmtNum>> GetReadStatementFromVariable(Variable var);
	std::shared_ptr<Procedure> GetCallsProcedureFromStatement(StmtNum stmt_num);
	std::shared_ptr<Variable> GetPrintVariableFromStatement(StmtNum stmt_num);
	std::shared_ptr<Variable> GetReadVariableFromStatement(StmtNum stmt_num);
private:
	ManyToOneRelationStore<StmtNum, RefType> statement_store_;
	std::unordered_set<StmtNum> statements_;
	std::unordered_map<Procedure, std::unordered_set<StmtNum>> calls_statements_;
	std::unordered_map<StmtNum, Procedure> calls_procedures_;
	std::unordered_map<Variable, std::unordered_set<StmtNum>> print_statements_;
	std::unordered_map<StmtNum, Variable> print_variables_;
	std::unordered_map<Variable, std::unordered_set<StmtNum>> read_statements_;
	std::unordered_map<StmtNum, Variable> read_variables_;
};