#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "../../Utils/type/RefType.h"
#include "../../Utils/type/TypeDef.h"

class StatementManager
{
public:
	void AddStatement(StmtNum stmt_num, RefType type);
	bool IsStatement(StmtNum stmt_num);
	RefType GetStatementType(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<StmtNum>> GetStatementsByType(RefType type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();

private:
	static std::unordered_map<RefType, std::unordered_set<StmtNum>> type_to_stmt_map_;
	static std::unordered_map<StmtNum,RefType> stmt_to_type_map_;
	static std::unordered_set<StmtNum> statements_;
	
};