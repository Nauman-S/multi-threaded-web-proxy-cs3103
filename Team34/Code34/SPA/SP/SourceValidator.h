#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "./tokenizer/SourceToken.h"

using namespace std;

class SourceValidator {
public:
    bool Validate(shared_ptr<vector<SourceToken>>);

 private:
    int idx = 0;
	vector<string> procedure_names;
	vector<string> variable_names;
    map<string, float> variable_map;
    vector<pair<string, string>> calls;
	bool ValidateProcedure(std::shared_ptr<vector<SourceToken>>);
	bool ValidateStatement(std::shared_ptr<vector<SourceToken>>);
	bool ValidateRead(std::shared_ptr<vector<SourceToken>>);
	bool ValidatePrint(std::shared_ptr<vector<SourceToken>>);
	bool ValidateCall(std::shared_ptr<vector<SourceToken>>);
	bool ValidateIf(std::shared_ptr<vector<SourceToken>>);
	bool ValidateWhile(std::shared_ptr<vector<SourceToken>>);
	bool ValidateAssign(std::shared_ptr<vector<SourceToken>>);
	bool ValidateExpression(std::shared_ptr<vector<SourceToken>>);
	bool ValidateArithmeticExpression(std::shared_ptr<vector<SourceToken>>);
	bool ValidateRelation(std::shared_ptr<vector<SourceToken>>);
    void IncrementIdx();
};