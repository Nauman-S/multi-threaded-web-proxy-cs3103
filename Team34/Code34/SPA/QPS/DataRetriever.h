#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

#include "reference/Ref.h"
#include "reference/ValType.h"
#include "relation/UsesSRel.h"
#include "relation/UsesPRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/ModifiesPRel.h"
#include "relation/RelType.h"
#include "query_result/ResWrapper.h"
#include "query_result/SetRes.h"
#include "query_result/TableRes.h"
#include "../PKB/ReadPKBManager.h"
// #include "relation/StmtVarRel.h"
// #include "relation/ProcVarRel.h"
// #include "relation/StmtStmtRel.h"
// #include "pattern/Pattern.h"
// Use forward declaration to avoid cyclic include of Visitor pattern
class StmtVarRel;
class ProcVarRel;
class StmtStmtRel;
class ProcProcRel;
class Pattern;


class DataRetriever
{
protected:
	std::shared_ptr<ReadPKBManager> pkb_ptr_;

	// Stmt-Var relations
	bool CheckSVRel(StmtVarRel& rel);																	// (stmt_num, var_name)
	bool CheckSVRelExistenceByStmt(StmtVarRel& rel);													// (stmt_num, wildcard)
	std::shared_ptr<std::unordered_set<std::string>> GetVarByStmt(StmtVarRel& rel);						// (stmt_num, synonym)
	std::shared_ptr<std::unordered_set<std::string>> GetStmtByVar(StmtVarRel& rel);						// (synonym, var_name)
	std::shared_ptr<std::unordered_set<std::string>> GetStmtByWildcard(StmtVarRel& rel);				// (synonym, wildcard)
	std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetAllSVRel(StmtVarRel& rel);		// (synonym, synonym)
	

	// Proc-Var relations
	bool CheckPVRel(ProcVarRel& rel);																	// (proc_name, var_name)
	bool CheckPVRelExistenceByProc(ProcVarRel& rel);													// (proc_name, wildcard)
	std::shared_ptr<std::unordered_set<std::string>> GetVarByProc(ProcVarRel& rel);						// (proc_name, synonym)
	std::shared_ptr<std::unordered_set<std::string>> GetProcByVar(ProcVarRel& rel);						// (synonym, var_name)
	std::shared_ptr<std::unordered_set<std::string>> GetProcByWildcard(ProcVarRel& rel);				// (synonym, wildcard)
	std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetAllPVRel(ProcVarRel& rel);		// (synonym, synonym)

	// Stmt-Stmt relations
	bool CheckSSRel(StmtStmtRel& rel);																	// (stmt_num, stmt_num)
	bool CheckSSRelExistence(StmtStmtRel& rel);															// (wildcard, wildcard)
	bool CheckSSRelExistenceByRhsStmt(StmtStmtRel& rel);												// (wildcard, stmt_num)
	bool CheckSSRelExistenceByLhsStmt(StmtStmtRel& rel);												// (stmt_num, wildcard)
	std::shared_ptr<std::unordered_set<std::string>> GetRhsStmtByLhsStmt(StmtStmtRel& rel);				// (stmt_num, synonym)
	std::shared_ptr<std::unordered_set<std::string>> GetRhsStmtByWildcard(StmtStmtRel& rel);			// (wildcard, synonym)
	std::shared_ptr<std::unordered_set<std::string>> GetLhsStmtByRhsStmt(StmtStmtRel& rel);				// (synonym, stmt_num)
	std::shared_ptr<std::unordered_set<std::string>> GetLhsStmtByWildcard(StmtStmtRel& rel);			// (synonym, wildcard)
	std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetAllSSRel(StmtStmtRel& rel);	// (synonym, synonym)

	// Assign Pattern
	std::shared_ptr<std::unordered_set<std::string>> GetAssignPatternStmtByVar(Pattern& pat);					// assign_syn(var_name, ExprSpec)
	std::shared_ptr<std::unordered_set<std::string>> GetAssignPatternStmtByWildcard(Pattern& pat);				// assign_syn(wildcard, ExprSpec)
	std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetAllAssignPattern(Pattern& pat);// assign_syn(var_syn, ExprSpec)

	// type conversion helpers
	std::shared_ptr<std::unordered_set<std::string>> IntSetToStrSet(std::shared_ptr<std::unordered_set<int>> set);
	std::shared_ptr<std::vector<std::pair<std::string, std::string>>> IntStrToStrStrTable(std::shared_ptr<std::vector<std::pair<int, std::string>>> table);
	std::shared_ptr<std::vector<std::pair<std::string, std::string>>> IntIntToStrStrTable(std::shared_ptr<std::vector<std::pair<int, int>>> table);
	
	// Filter helpers
	std::shared_ptr<std::unordered_set<int>> FilterStmtSetByType(std::shared_ptr<std::unordered_set<int>> stmts, RefType stmt_type);
	std::shared_ptr<std::vector<std::pair<int, std::string>>> FilterStmtTableByType(std::shared_ptr<std::vector<std::pair<int, std::string>>> table, RefType stmt_type);
	std::shared_ptr<std::vector<std::pair<int, int>>> FilterStmtTableByType(std::shared_ptr<std::vector<std::pair<int, int>>> table, RefType lhs_stmt_type, RefType rhs_stmt_type);

public:
	DataRetriever() {
		pkb_ptr_ = std::move(ReadPKBManager::GetInstance());
	};

	DataRetriever(std::shared_ptr<ReadPKBManager> pkb) : pkb_ptr_{ pkb } {};

	std::shared_ptr<ResWrapper> retrieve(StmtVarRel& rel);

	std::shared_ptr<ResWrapper> retrieve(ProcVarRel& rel);

	std::shared_ptr<ResWrapper> retrieve(StmtStmtRel& rel);

	std::shared_ptr<ResWrapper> retrieve(ProcProcRel& rel);

	std::shared_ptr<ResWrapper> retrieve(Pattern& pat);

	std::shared_ptr<ResWrapper> retrieve(std::shared_ptr<Ref> ref_ptr);
};
