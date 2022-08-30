#pragma once

#include <memory>

#include "relation/StmtVarRel.h"
#include "relation/ProcVarRel.h"
#include "relation/StmtStmtRel.h"
#include "relation/UsesSRel.h"
#include "relation/UsesPRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/ModifiesPRel.h"
#include "reference/ValType.h"
#include "query_result/QueryResult.h"

using std::unordered_set;
using std::string;

class DataRetriever
{
protected:

	// Stmt-Var relations
	bool CheckSVRel(StmtVarRel rel);
	unordered_set<string>& GetVarByStmt(StmtVarRel rel);
	unordered_set<string>& GetStmtByVar(StmtVarRel rel);

	// Proc-Var relations
	bool CheckPVRel(ProcVarRel rel);
	unordered_set<string>& GetVarByProc(ProcVarRel rel);
	unordered_set<string>& GetProcByVar(ProcVarRel rel);

public:
	std::shared_ptr<QueryResult> retrieve(const StmtVarRel rel);

	std::shared_ptr<QueryResult> retrieve(const ProcVarRel rel);

	// TODO
	// const QueryResult& retrieve(const StmtStmtRel rel);
};

