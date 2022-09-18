#pragma once

#include <cassert>
#include <unordered_map>
#include <memory>
#include <vector>

#include "../../Utils/type/TypeDef.h"
#include "../../Utils/expression/ExprSpec.h"
#include "../../Utils/expression/Expr.h"

class PatternManager
{
public:
	// Assign Pattern methods
	void AddAssignPattern(StmtNum stmt_num, Variable var, Expr expr);
	bool IsAssignPatternMatch(StmtNum stmt_num, std::shared_ptr<ExprSpec> expr);
	bool IsAssignPatternMatch(StmtNum stmt_num, Variable var, std::shared_ptr<ExprSpec> expr);
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAssignPatternMatch(std::shared_ptr<ExprSpec> expr);
private:
	std::unordered_map<StmtNum, std::pair<Variable, std::shared_ptr<Expr>>> assign_statement_map_;
};