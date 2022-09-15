#pragma once

#include <cassert>
#include <unordered_map>
#include <memory>
#include <vector>

#include "../../Utils/type/TypeDef.h"

class PatternManager
{
public:
	// Assign Pattern methods
	void AddAssignPattern(StmtNum stmt_num, Variable var, std::string expr);
	bool IsAssignPatternMatch(StmtNum stmt_num, std::string expr, bool is_exact_match);
	bool IsAssignPatternMatch(StmtNum stmt_num, Variable var, std::string expr, bool is_exact_match);
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAssignPatternMatch(std::string expr, bool is_exact_match);
private:
	// A map that maps statement number -> pair<Variable, Postfix Expression>
	std::unordered_map<StmtNum, std::pair<Variable, std::string>> assign_statement_map_;
};