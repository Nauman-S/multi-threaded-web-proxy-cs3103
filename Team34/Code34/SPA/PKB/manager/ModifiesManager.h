#pragma once

#include <vector>
#include <unordered_set>

#include "../store/RelationStore.h"
#include "../../Utils/type/TypeDef.h"

class ModifiesManager
{
public:
	bool CheckModifies(StmtNum stmt_num, Variable var);
	bool CheckModifies(Procedure proc_name, Variable var);
	void SetModifies(StmtNum stmt_num, Variable var);
	void SetModifies(Procedure proc_name, Variable var);
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies();
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies();
	std::shared_ptr<std::unordered_set<Variable>> GetVarByStmtNum(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<Variable>> GetVarByProcName(Procedure proc_name);
	std::shared_ptr<std::unordered_set<StmtNum>> GetStmtNumByVar(Variable var);
	std::shared_ptr<std::unordered_set<Procedure>> GetProcNameByVar(Variable var);
private:
	RelationStore<Procedure, Variable> modifies_pv_store_;
	RelationStore<StmtNum, Variable> modifies_sv_store_;
};