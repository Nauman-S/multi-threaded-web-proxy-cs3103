#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

#include "reference/Ref.h"
#include "reference/ValType.h"
//#include "relation/StmtVarRel.h"
//#include "relation/ProcVarRel.h"
//#include "relation/StmtStmtRel.h"
// Use forward declaration to avoid cyclic include of Visitor pattern
class StmtVarRel;
class ProcVarRel;
class StmtStmtRel;
#include "relation/UsesSRel.h"
#include "relation/UsesPRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/ModifiesPRel.h"
#include "relation/RelType.h"
#include "query_result/ResWrapper.h"
#include "query_result/SetRes.h"
#include "query_result/TableRes.h"
#include "../PKB/ReadPKBManager.h"


using std::string;
using std::unordered_set;
using std::vector;
using std::pair;

class DataRetriever
{
protected:
	std::unique_ptr<ReadPKBManager> pkb_ptr_;

	// Stmt-Var relations
	bool CheckSVRel(StmtVarRel rel);
	std::shared_ptr<unordered_set<string>> GetVarByStmt(StmtVarRel rel);
	std::shared_ptr<unordered_set<string>> GetStmtByVar(StmtVarRel rel);
	std::shared_ptr<vector<pair<string, string>>> GetAllSVRel(StmtVarRel rel);
	

	// Proc-Var relations
	bool CheckPVRel(ProcVarRel rel);
	std::shared_ptr<unordered_set<string>> GetVarByProc(ProcVarRel rel);
	std::shared_ptr<unordered_set<string>> GetProcByVar(ProcVarRel rel);
	std::shared_ptr<vector<pair<string, string>>> GetAllPVRel(ProcVarRel rel);

	// Stmt-Stmt relations
	/*bool CheckSSRel(ProcVarRel rel);
	unordered_set<string>& GetRhsStmtByLhsStmt(ProcVarRel rel);
	unordered_set<string>& GetLhsStmtByRhsStmt(ProcVarRel rel);
	const vector<pair<string, string>>& GetAllSSRel(ProcVarRel rel);*/

	std::shared_ptr<unordered_set<string>> IntSetToStrSet(std::shared_ptr<unordered_set<int>> set);
	std::shared_ptr<vector<pair<string, string>>> IntStrToStrStrTable(vector<pair<int, string>> table);
	

public:
	DataRetriever() {};

	DataRetriever(std::unique_ptr<ReadPKBManager> pkb) : pkb_ptr_{ std::move(pkb) } {};

	std::shared_ptr<ResWrapper> retrieve(StmtVarRel rel);

	std::shared_ptr<ResWrapper> retrieve(ProcVarRel rel);

	// TODO
	//std::unique_ptr<ResWrapper> retrieve(StmtStmtRel rel);

	std::shared_ptr<ResWrapper> retrieve(std::shared_ptr<Ref> ref_ptr);
};
