#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../../Utils/type/TypeDef.h"
                                                                                                                                                                                                                                                    
class PatternStore
{
public:
	void AddPattern(StmtNum stmt_num, Variable var);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatmentsFromVar(Variable var);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllPatterns();

	void Clear();
private:
	std::unordered_map<Variable, std::unordered_set<StmtNum>> var_to_stmt_map_;
	std::unordered_set<StmtNum> all_statements_;
	std::vector<std::pair<StmtNum, Variable>> all_sv_pairs_;
};