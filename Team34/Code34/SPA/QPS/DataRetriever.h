#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

#include "reference/ValType.h"
#include "relation/StmtVarRel.h"
#include "relation/ProcVarRel.h"
#include "relation/StmtStmtRel.h"
#include "relation/UsesSRel.h"
#include "relation/UsesPRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/ModifiesPRel.h"
#include "query_result/ResWrapper.h"
#include "query_result/SetRes.h"
#include "query_result/TableRes.h"

using std::string;
using std::unordered_set;
using std::vector;
using std::pair;

class DataRetriever
{
protected:

	// Stmt-Var relations
	bool CheckSVRel(StmtVarRel rel);
	unordered_set<string>& GetVarByStmt(StmtVarRel rel);
	unordered_set<string>& GetStmtByVar(StmtVarRel rel);
	const vector<pair<string, string>>& GetAllSVRel(StmtVarRel rel);
	

	// Proc-Var relations
	bool CheckPVRel(ProcVarRel rel);
	unordered_set<string>& GetVarByProc(ProcVarRel rel);
	unordered_set<string>& GetProcByVar(ProcVarRel rel);
	const vector<pair<string, string>>& GetAllPVRel(ProcVarRel rel);

	// Stmt-Stmt relations
	/*bool CheckSSRel(ProcVarRel rel);
	unordered_set<string>& GetRhsStmtByLhsStmt(ProcVarRel rel);
	unordered_set<string>& GetLhsStmtByRhsStmt(ProcVarRel rel);
	const vector<pair<string, string>>& GetAllSSRel(ProcVarRel rel);*/

public:
	std::unique_ptr<ResWrapper> retrieve(StmtVarRel rel);

	std::unique_ptr<ResWrapper> retrieve(ProcVarRel rel);

	// TODO
	// std::unique_ptr<ResWrapper> retrieve(StmtStmtRel rel);
};

