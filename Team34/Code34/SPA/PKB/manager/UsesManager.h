#pragma once

#include <memory>
#include <vector>
#include <unordered_set>

#include "../store/ManyToManyRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class UsesManager
{
public:
	bool CheckUses(StmtNum stmt_num, Variable var);
	bool CheckUses(Procedure proc_name, Variable var);
	void SetUses(StmtNum stmt_num, Variable var);
	void SetUses(Procedure proc_name, Variable var);
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVUses();
	std::shared_ptr <std::vector<std::pair<Procedure, Variable>>> GetAllPVUses();
	std::shared_ptr <std::unordered_set<Variable>> GetVarByStmtNum(StmtNum stmt_num);
	std::shared_ptr <std::unordered_set<Variable>> GetVarByProcName(Procedure proc_name);
	std::shared_ptr <std::unordered_set<StmtNum>> GetStmtNumByVar(Variable var);
	std::shared_ptr <std::unordered_set<Procedure>> GetProcNameByVar(Variable var);
private:
	ManyToManyRelationStore<Procedure, Variable> uses_pv_store_;
	ManyToManyRelationStore<StmtNum, Variable> uses_sv_store_;
};