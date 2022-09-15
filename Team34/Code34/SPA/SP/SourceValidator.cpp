#include "SourceValidator.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include "../Utils/algo/TopoCycle.h"
using namespace std;

bool SourceValidator::Validate(vector<SourceToken> tokens) {
	int idx = 0;
	vector<string> procedure_names;
	vector<string> variable_names;
    // cyclic call have not done
	map<string, float> variable_map;
	map<string, string> calls;
	while (idx < (int) tokens.size()) {
		if (!ValidateProcedure(tokens, idx, procedure_names, variable_names, variable_map, calls)) {
			return false;
		}
	}
	for (auto const& x : calls) {
		if (!count(procedure_names.begin(), procedure_names.end(), x.first) || !count(procedure_names.begin(), procedure_names.end(), x.second)) {
			return false;
		}
	}
	TopoCycle checker = TopoCycle();
	if (checker.CheckCycle(calls, procedure_names)) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateProcedure(vector<SourceToken> tokens, int& idx, vector<string>& procedure_names, vector<string>& variable_names, map<string, float>& variable_map, map<string, string>& calls) {
	if (!tokens.at(idx++).IsProcedure()) {
		return false;
	}
	if (tokens.at(idx).GetType() != SourceTokenType::kName) {
		return false;
	}
	if (count(procedure_names.begin(), procedure_names.end(), tokens.at(idx).GetStringVal()) || count(variable_names.begin(), variable_names.end(), tokens.at(idx).GetStringVal())) {
		return false;
	}
	procedure_names.push_back(tokens.at(idx++).GetStringVal());
	if (tokens.at(idx++).GetType() != SourceTokenType::kLeftCurly) {
		return false;
	}
	if (!ValidateStatement(tokens, idx, procedure_names, variable_names, variable_map, calls)) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kRightCurly) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateStatement(vector<SourceToken> tokens, int& idx, vector<string>& procedure_names, vector<string>& variable_names, map<string, float>& variable_map, map<string, string>& calls) {
	while (tokens.at(idx).GetType() != SourceTokenType::kRightCurly) {
		if (tokens.at(idx).IsRead()) {
			if (!ValidateRead(tokens, ++idx, procedure_names, variable_names)) {
				return false;
			}
		}
		else if (tokens.at(idx).IsPrint()) {
			if (!ValidatePrint(tokens, ++idx, variable_names)) {
				return false;
			}
		}
		else if (tokens.at(idx).IsCall()) {
			if (!ValidateCall(tokens, ++idx, procedure_names, calls)) {
				return false;
			}
		}
		else if (tokens.at(idx).IsIf()) {
			if (!ValidateIf(tokens, ++idx, procedure_names, variable_names, variable_map, calls)) {
				return false;
			}
		}
		else if (tokens.at(idx).IsWhile()) {
			if (!ValidateWhile(tokens, ++idx, procedure_names, variable_names, variable_map, calls)) {
				return false;
			}
		}
		else {
			if (!ValidateAssign(tokens, idx, procedure_names, variable_names, variable_map)) {
				return false;
			}
		}
	}
	return true;
}

bool SourceValidator::ValidateRead(vector<SourceToken> tokens, int& idx, vector<string>& procedure_names, vector<string>& variable_names) {
	if (tokens.at(idx).GetType() != SourceTokenType::kName) {
		return false;
	}
	if (count(procedure_names.begin(), procedure_names.end(), tokens.at(idx).GetStringVal())) {
		return false;
	} 
	else {
		variable_names.push_back(tokens.at(idx++).GetStringVal());
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kSemiColon) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidatePrint(vector<SourceToken> tokens, int& idx, vector<string>& variable_names) {
	if (!count(variable_names.begin(), variable_names.end(), tokens.at(idx).GetStringVal())) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kName) {
		return false;
	}

	if (tokens.at(idx++).GetType() != SourceTokenType::kSemiColon) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateCall(vector<SourceToken> tokens, int& idx, vector<string>& procedure_names, map<string, string>& calls) {
	if (tokens.at(idx).GetType() != SourceTokenType::kName) {
		return false;
	}
	calls.insert(pair<string, string>(procedure_names.at(procedure_names.size() - 1), tokens.at(idx++).GetStringVal()));
	
	if (tokens.at(idx++).GetType() != SourceTokenType::kSemiColon) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateIf(vector<SourceToken> tokens, int& idx, vector<string>& procedure_names, vector<string>& variable_names, map<string, float>& variable_map, map<string, string>& calls) {
	if (tokens.at(idx++).GetType() != SourceTokenType::kLeftRound) {
		return false;
	}
	if (!ValidateExpression(tokens, idx, variable_names, variable_map)) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kRightRound) {
		return false;
	}
	if (!tokens.at(idx++).IsThen()) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kLeftCurly) {
		return false;
	}
	if (!ValidateStatement(tokens, idx, procedure_names, variable_names, variable_map, calls)) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kRightCurly) {
		return false;
	}
	if (!tokens.at(idx++).IsElse()) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kLeftCurly) {
		return false;
	}
	if (!ValidateStatement(tokens, idx, procedure_names, variable_names, variable_map, calls)) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kRightCurly) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateWhile(vector<SourceToken> tokens, int& idx, vector<string>& procedure_names, vector<string>& variable_names, map<string, float>& variable_map, map<string, string>& calls) {
	if (tokens.at(idx++).GetType() != SourceTokenType::kLeftRound) {
		return false;
	}
	if (!ValidateExpression(tokens, idx, variable_names, variable_map)) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kRightRound) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kLeftCurly) {
		return false;
	}
	if (!ValidateStatement(tokens, idx, procedure_names, variable_names, variable_map, calls)) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kRightCurly) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateAssign(vector<SourceToken> tokens, int& idx, vector<string>& procedure_names, vector<string>& variable_names, map<string, float>& variable_map) {
	if (tokens.at(idx).GetType() != SourceTokenType::kName) {
		return false;
	}
	if (count(procedure_names.begin(), procedure_names.end(), tokens.at(idx).GetStringVal())) {
		return false;
	}
	variable_names.push_back(tokens.at(idx++).GetStringVal());
	if (tokens.at(idx++).GetType() != SourceTokenType::kEqual) {
		return false;
	}
	if (!ValidateArithmeticExpression(tokens, idx, variable_names, variable_map)) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kSemiColon) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateExpression(vector<SourceToken> tokens, int& idx, vector<string>& variable_names, map<string, float>& variable_map) {
	if (tokens.at(idx).GetType() == SourceTokenType::kNegate) {
		idx += 1;
		if (tokens.at(idx++).GetType() != SourceTokenType::kLeftRound) {
			return false;
		}
		if (!ValidateExpression(tokens, idx, variable_names, variable_map)) {
			return false;
		}
		if (tokens.at(idx++).GetType() != SourceTokenType::kRightRound) {
			return false;
		}
		return true;
	}
	else if (tokens.at(idx).GetType() == SourceTokenType::kLeftRound) {
		int temp = idx;
		idx += 1;
		bool flag = true;
		if (flag && !ValidateExpression(tokens, idx, variable_names, variable_map)) {
			flag = false;
		}
		if (flag && tokens.at(idx++).GetType() != SourceTokenType::kRightRound) {
			flag = false;
		}
		if (flag && tokens.at(idx).GetType() != SourceTokenType::kLogicalAnd && tokens.at(idx).GetType() != SourceTokenType::kLogicalOr) {
			flag = false;
		}
		idx += 1;
		if (flag && tokens.at(idx++).GetType() != SourceTokenType::kLeftRound) {
			flag = false;
		}
		if (flag && !ValidateExpression(tokens, idx, variable_names, variable_map)) {
			flag = false;
		}
		if (flag && tokens.at(idx++).GetType() != SourceTokenType::kRightRound) {
			flag = false;
		}
		if (flag) {
			return true;
		}
		else {
			idx = temp;
			return ValidateRelation(tokens, idx, variable_names, variable_map);
		}
	}
	else {
		return ValidateRelation(tokens, idx, variable_names, variable_map);
	}
}

bool SourceValidator::ValidateArithmeticExpression(vector<SourceToken> tokens, int& idx, vector<string>& variable_names, map<string, float>& variable_map) {
	int cnt = 0;
	string expected = "var";
	while (tokens.at(idx).GetType() == SourceTokenType::kName || tokens.at(idx).GetType() == SourceTokenType::kInteger || tokens.at(idx).GetType() == SourceTokenType::kLeftRound || tokens.at(idx).GetType() == SourceTokenType::kRightRound || tokens.at(idx).GetType()== SourceTokenType::kAdd || tokens.at(idx).GetType() == SourceTokenType::kMinus || tokens.at(idx).GetType() == SourceTokenType::kMultiply || tokens.at(idx).GetType() == SourceTokenType::kDivide || tokens.at(idx).GetType() == SourceTokenType::kModulo) {
		if (expected == "var" && tokens.at(idx).GetType() == SourceTokenType::kName) {
			if (!count(variable_names.begin(), variable_names.end(), tokens.at(idx).GetStringVal())) {
				return false;
			}
			expected = "sign";
		}
		else if (expected == "var" && tokens.at(idx).GetType() == SourceTokenType::kInteger) {
			expected = "sign";
		}
		else if (expected == "var" && tokens.at(idx).GetType() == SourceTokenType::kLeftRound) {
			cnt += 1;
		}
		else if (expected == "sign" && tokens.at(idx).GetType() == SourceTokenType::kRightRound && cnt > 0) {
			cnt -= 1;
		}
		else if (expected == "sign" && tokens.at(idx).GetType() == SourceTokenType::kRightRound && cnt == 0) {
			return true;
		}
		else if (expected == "sign" && tokens.at(idx).GetType() == SourceTokenType::kAdd) {
			expected = "var";
		}
		else if (expected == "sign" && tokens.at(idx).GetType() == SourceTokenType::kDivide) {
			expected = "var";
		}
		else if (expected == "sign" && tokens.at(idx).GetType() == SourceTokenType::kMinus) {
			expected = "var";
		}
		else if (expected == "sign" && tokens.at(idx).GetType() == SourceTokenType::kModulo) {
			expected = "var";
		}
		else if (expected == "sign" && tokens.at(idx).GetType() == SourceTokenType::kMultiply) {
			expected = "var";
		}
		else {
			return false;
		}
		idx += 1;
	}
	if (cnt != 0) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateRelation(vector<SourceToken> tokens, int& idx, vector<string>& variable_names, map<string, float>& variable_map) {
	if (!ValidateArithmeticExpression(tokens, idx, variable_names, variable_map)) {
		return false;
	}
	if (tokens.at(idx).GetType() != SourceTokenType::kLesser && tokens.at(idx).GetType() != SourceTokenType::kLesserEqual && tokens.at(idx).GetType() != SourceTokenType::kGreater && tokens.at(idx).GetType() != SourceTokenType::kGreaterEqual && tokens.at(idx).GetType() != SourceTokenType::kNotEqual && tokens.at(idx).GetType() != SourceTokenType::kDoubleEqual) {
		return false;
	}
	idx += 1;
	if (!ValidateArithmeticExpression(tokens, idx, variable_names, variable_map)) {
		return false;
	}
	return true;
}