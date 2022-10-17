#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "./tokenizer/SourceToken.h"

using namespace std;

class SourceValidator {
public:
    void SetTokens(shared_ptr<vector<SourceToken>>);
    bool Validate();

private:
    int idx = 0;
    vector<string> procedure_names;
    vector<string> variable_names;
    map<string, float> variable_map;
    vector<pair<string, string>> calls;
    shared_ptr<vector<SourceToken>> tokens;
    bool ValidateProcedure();
    bool ValidateStatement();
    bool ValidateRead();
    bool ValidatePrint();
    bool ValidateCall();
    bool ValidateIf();
    bool ValidateWhile();
    bool ValidateAssign();
    bool ValidateExpression();
    bool ValidateArithmeticExpression();
    bool ValidateRelation();
    void IncrementIdx();
};