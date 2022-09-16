#pragma once

#include <vector>
#include <unordered_set>

#include "../store/ManyToManyRelationStore.h"
#include "../store/ManyToOneRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class ModifiesManager
{
public:
	void SetModifies(StmtNum stmt_num, Variable var);
	void SetModifies(Procedure proc_name, Variable var);
	bool CheckModifies(StmtNum stmt_num, Variable var);
	bool CheckModifies(Procedure proc_name, Variable var);
	std::shared_ptr<Variable> GetVarByStmtNum(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<Variable>> GetVarByProcName(Procedure proc_name);
	std::shared_ptr<std::unordered_set<StmtNum>> GetStmtNumByVar(Variable var);
	std::shared_ptr<std::unordered_set<Procedure>> GetProcNameByVar(Variable var);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();
	std::shared_ptr<std::unordered_set<Procedure>> GetAllProcedures();
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies();
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies();
private:
	ManyToManyRelationStore<Procedure, Variable> modifies_pv_store_;
	ManyToOneRelationStore<StmtNum, Variable> modifies_sv_store_;
};