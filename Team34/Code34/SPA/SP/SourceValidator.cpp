#include "SourceValidator.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

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
	return true;
}

bool SourceValidator::ValidateProcedure(vector<SourceToken> tokens, int& idx, vector<string>& procedure_names, vector<string>& variable_names, map<string, float>& variable_map, map<string, string>& calls) {
	if (tokens.at(idx++).GetType() != SourceTokenType::kProcedure) {
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
		if (tokens.at(idx).GetType() != SourceTokenType::kRightCurly) {
			if (tokens.at(idx).GetType() == SourceTokenType::kRead) {
				if (!ValidateRead(tokens, ++idx, procedure_names, variable_names)) {
					return false;
				}
			}
			else if (tokens.at(idx).GetType() == SourceTokenType::kPrint) {
				if (!ValidatePrint(tokens, ++idx, variable_names)) {
					return false;
				}
			}
			else if (tokens.at(idx).GetType() == SourceTokenType::kCall) {
				if (!ValidateCall(tokens, ++idx, procedure_names, calls)) {
					return false;
				}
			}
			else if (tokens.at(idx).GetType() == SourceTokenType::kIf) {
				if (!ValidateIf(tokens, ++idx, procedure_names, variable_names, variable_map, calls)) {
					return false;
				}
			}
			else if (tokens.at(idx).GetType() == SourceTokenType::kWhile) {
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
	else if (count(variable_names.begin(), variable_names.end(), tokens.at(idx).GetStringVal())) {
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
	if (tokens.at(idx++).GetType() != SourceTokenType::kThen) {
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
	if (tokens.at(idx++).GetType() != SourceTokenType::kElse) {
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
	if (!ValidateExpression(tokens, idx, variable_names, variable_map)) {
		return false;
	}
	if (tokens.at(idx++).GetType() != SourceTokenType::kSemiColon) {
		return false;
	}
	return true;
}

bool SourceValidator::ValidateExpression(vector<SourceToken> tokens, int& idx, vector<string>& variable_names, map<string, float>& variable_map) {
	while (tokens.at(idx).GetType() != SourceTokenType::kSemiColon && tokens.at(idx).GetType() != SourceTokenType::kRightRound) {
		if (tokens.at(idx).GetType() == SourceTokenType::kName) {
			if (!count(variable_names.begin(), variable_names.end(), tokens.at(idx).GetStringVal())) {
				return false;
			}
		}
		else {
		}
		idx += 1;
	}
	return true;
}