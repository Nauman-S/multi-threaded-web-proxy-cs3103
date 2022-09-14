#pragma once

#include <unordered_map>
#include <cassert>

#include "../../Utils/type/TypeDef.h"

class PatternManager
{
public:
	// Assign Pattern methods
	void AddAssignPattern(StmtNum stmt_num, Variable var, std::string expr);
	bool IsAssignPatternExactMatch(StmtNum stmt_num, Variable var, std::string expr);
	bool IsAssignPatternExactMatch(StmtNum stmt_num, std::string expr);
	bool IsAssignPatternPartialMatch(StmtNum stmt_num, Variable var, std::string expr);
	bool IsAssignPatternPartialMatch(StmtNum stmt_num, std::string expr);
private:
	bool IsAssignPatternExprHelper(StmtNum stmt_num, std::string expr, bool isExactMatch);
	bool IsAssignPatternVarExprHelper(StmtNum stmt_num, Variable var, std::string expr, bool isExactMatch);
	// A map that maps statement number -> pair<Variable, Postfix Expression>
	std::unordered_map<StmtNum, std::pair<Variable, std::string>> assign_statement_map_;
};