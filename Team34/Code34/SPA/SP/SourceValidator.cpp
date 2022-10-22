#include "SourceValidator.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include "../Utils/algo/TopoCycle.h"

using namespace std;

bool SourceValidator::Validate() {
    while (idx < (int)tokens->size()) {
        if (!ValidateProcedure()) {
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

bool SourceValidator::ValidateProcedure() {
    if (!tokens->at(idx++).IsProcedure()) {
        return false;
    }
    if (tokens->at(idx).GetType() != SourceTokenType::kName) {
        return false;
    }
    if (std::find(procedure_names.begin(), procedure_names.end(), tokens->at(idx).GetStringVal()) != procedure_names.end()) {
        return false;
    }
    procedure_names.push_back(tokens->at(idx++).GetStringVal());
    if (tokens->at(idx++).GetType() != SourceTokenType::kLeftCurly) {
        return false;
    }
    if (!ValidateStatement()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kRightCurly) {
        return false;
    }
    return true;
}

bool SourceValidator::ValidateStatement() {
    while (tokens->at(idx).GetType() != SourceTokenType::kRightCurly) {
        int tmp = idx;
        if (ValidateAssign()) {
            continue;
        }
        else {
            idx = tmp;
        }
        if (tokens->at(idx).IsRead()) {
            IncrementIdx();
            if (!ValidateRead()) {
                return false;
            }
        }
        else if (tokens->at(idx).IsPrint()) {
            IncrementIdx();
            if (!ValidatePrint()) {
                return false;
            }
        }
        else if (tokens->at(idx).IsCall()) {
            IncrementIdx();
            if (!ValidateCall()) {
                return false;
            }
        }
        else if (tokens->at(idx).IsIf()) {
            IncrementIdx();
            if (!ValidateIf()) {
                return false;
            }
        }
        else if (tokens->at(idx).IsWhile()) {
            IncrementIdx();
            if (!ValidateWhile()) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return true;
}

bool SourceValidator::ValidateRead() {
    if (tokens->at(idx).GetType() != SourceTokenType::kName) {
        return false;
    }
    variable_names.push_back(tokens->at(idx++).GetStringVal());
    if (tokens->at(idx++).GetType() != SourceTokenType::kSemiColon) {
        return false;
    }
    return true;
}

bool SourceValidator::ValidatePrint() {
    if (tokens->at(idx++).GetType() != SourceTokenType::kName) {
        return false;
    }

    if (tokens->at(idx++).GetType() != SourceTokenType::kSemiColon) {
        return false;
    }
    return true;
}

bool SourceValidator::ValidateCall() {
    if (tokens->at(idx).GetType() != SourceTokenType::kName) {
        return false;
    }
    calls.push_back(pair<string, string>(procedure_names.at(procedure_names.size() - 1), tokens->at(idx++).GetStringVal()));
    if (tokens->at(idx++).GetType() != SourceTokenType::kSemiColon) {
        return false;
    }
    return true;
}

bool SourceValidator::ValidateIf() {
    if (tokens->at(idx++).GetType() != SourceTokenType::kLeftRound) {
        return false;
    }
    if (!ValidateExpression()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kRightRound) {
        return false;
    }
    if (!tokens->at(idx++).IsThen()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kLeftCurly) {
        return false;
    }
    if (!ValidateStatement()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kRightCurly) {
        return false;
    }
    if (!tokens->at(idx++).IsElse()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kLeftCurly) {
        return false;
    }
    if (!ValidateStatement()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kRightCurly) {
        return false;
    }
    return true;
}

bool SourceValidator::ValidateWhile() {
    if (tokens->at(idx++).GetType() != SourceTokenType::kLeftRound) {
        return false;
    }
    if (!ValidateExpression()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kRightRound) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kLeftCurly) {
        return false;
    }
    if (!ValidateStatement()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kRightCurly) {
        return false;
    }
    return true;
}

bool SourceValidator::ValidateAssign() {
    if (tokens->at(idx).GetType() != SourceTokenType::kName) {
        return false;
    }
    variable_names.push_back(tokens->at(idx++).GetStringVal());
    if (tokens->at(idx++).GetType() != SourceTokenType::kEqual) {
        return false;
    }
    if (!ValidateArithmeticExpression()) {
        return false;
    }
    if (tokens->at(idx++).GetType() != SourceTokenType::kSemiColon) {
        return false;
    }
    return true;
}

bool SourceValidator::ValidateExpression() {
    if (tokens->at(idx).GetType() == SourceTokenType::kNegate) {
        IncrementIdx();
        if (tokens->at(idx++).GetType() != SourceTokenType::kLeftRound) {
            return false;
        }
        if (!ValidateExpression()) {
            return false;
        }
        if (tokens->at(idx++).GetType() != SourceTokenType::kRightRound) {
            return false;
        }
        return true;
    }
    else if (tokens->at(idx).GetType() == SourceTokenType::kLeftRound) {
        int temp = idx;
        IncrementIdx();
        bool flag = true;
        if (flag && !ValidateExpression()) {
            flag = false;
        }
        if (flag && tokens->at(idx++).GetType() != SourceTokenType::kRightRound) {
            flag = false;
        }
        if (flag && tokens->at(idx).GetType() != SourceTokenType::kLogicalAnd && tokens->at(idx).GetType() != SourceTokenType::kLogicalOr) {
            flag = false;
        }
        IncrementIdx();
        if (flag && tokens->at(idx++).GetType() != SourceTokenType::kLeftRound) {
            flag = false;
        }
        if (flag && !ValidateExpression()) {
            flag = false;
        }
        if (flag && tokens->at(idx++).GetType() != SourceTokenType::kRightRound) {
            flag = false;
        }
        if (flag) {
            return true;
        }
        else {
            idx = temp;
            return ValidateRelation();
        }
    }
    else {
        return ValidateRelation();
    }
}

bool SourceValidator::ValidateArithmeticExpression() {
    int cnt = 0;
    string expected = "var";
    while (tokens->at(idx).GetType() == SourceTokenType::kName || tokens->at(idx).GetType() == SourceTokenType::kInteger || tokens->at(idx).GetType() == SourceTokenType::kLeftRound || tokens->at(idx).GetType() == SourceTokenType::kRightRound || tokens->at(idx).GetType() == SourceTokenType::kAdd || tokens->at(idx).GetType() == SourceTokenType::kMinus || tokens->at(idx).GetType() == SourceTokenType::kMultiply || tokens->at(idx).GetType() == SourceTokenType::kDivide || tokens->at(idx).GetType() == SourceTokenType::kModulo) {
        if (expected == "var" && tokens->at(idx).GetType() == SourceTokenType::kName) {
            expected = "sign";
        }
        else if (expected == "var" && tokens->at(idx).GetType() == SourceTokenType::kInteger) {
            expected = "sign";
        }
        else if (expected == "var" && tokens->at(idx).GetType() == SourceTokenType::kLeftRound) {
            cnt += 1;
        }
        else if (expected == "sign" && tokens->at(idx).GetType() == SourceTokenType::kRightRound && cnt > 0) {
            cnt -= 1;
        }
        else if (expected == "sign" && tokens->at(idx).GetType() == SourceTokenType::kRightRound && cnt == 0) {
            return true;
        }
        else if (expected == "sign" && tokens->at(idx).GetType() == SourceTokenType::kAdd) {
            expected = "var";
        }
        else if (expected == "sign" && tokens->at(idx).GetType() == SourceTokenType::kDivide) {
            expected = "var";
        }
        else if (expected == "sign" && tokens->at(idx).GetType() == SourceTokenType::kMinus) {
            expected = "var";
        }
        else if (expected == "sign" && tokens->at(idx).GetType() == SourceTokenType::kModulo) {
            expected = "var";
        }
        else if (expected == "sign" && tokens->at(idx).GetType() == SourceTokenType::kMultiply) {
            expected = "var";
        }
        else {
            return false;
        }
        IncrementIdx();
    }
    if (cnt != 0) {
        return false;
    }
    return true;
}

bool SourceValidator::ValidateRelation() {
    if (!ValidateArithmeticExpression()) {
        return false;
    }
    if (tokens->at(idx).GetType() != SourceTokenType::kLesser && tokens->at(idx).GetType() != SourceTokenType::kLesserEqual && tokens->at(idx).GetType() != SourceTokenType::kGreater && tokens->at(idx).GetType() != SourceTokenType::kGreaterEqual && tokens->at(idx).GetType() != SourceTokenType::kNotEqual && tokens->at(idx).GetType() != SourceTokenType::kDoubleEqual) {
        return false;
    }
    IncrementIdx();
    if (!ValidateArithmeticExpression()) {
        return false;
    }
    return true;
}

void SourceValidator::IncrementIdx() { idx += 1; }

void SourceValidator::SetTokens(shared_ptr<vector<SourceToken>> source_tokens) {
    tokens = source_tokens;
}