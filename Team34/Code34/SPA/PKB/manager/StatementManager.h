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
	std::shared_ptr<RefType> GetStatementType(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<StmtNum>> GetStatementsByType(RefType type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();
private:
	ManyToOneRelationStore<StmtNum, RefType> statement_store_;
	std::unordered_set<StmtNum> statements_;
};