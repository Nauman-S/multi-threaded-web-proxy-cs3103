#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "./tokenizer/SourceToken.h"

using namespace std;

class SourceValidator {
public:
	bool Validate(std::shared_ptr<vector<SourceToken>>);

private:
	bool ValidateProcedure(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, vector<string>&, map<string, float>&, vector<pair<string, string>>&);
	bool ValidateStatement(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, vector<string>&, map<string, float>&, vector<pair<string, string>>&);
	bool ValidateRead(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, vector<string>&);
	bool ValidatePrint(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&);
	bool ValidateCall(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, vector<pair<string, string>>&);
	bool ValidateIf(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, vector<string>&, map<string, float>&, vector<pair<string, string>>&);
	bool ValidateWhile(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, vector<string>&, map<string, float>&, vector<pair<string, string>>&);
	bool ValidateAssign(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, vector<string>&, map<string, float>&);
	bool ValidateExpression(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, map<string, float>&);
	bool ValidateArithmeticExpression(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, map<string, float>&);
	bool ValidateRelation(std::shared_ptr<vector<SourceToken>>, int&, vector<string>&, map<string, float>&);
};