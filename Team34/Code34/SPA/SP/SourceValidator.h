#pragma once
#include <vector>
#include <string>
#include <map>
#include "SourceToken.h"

using namespace std;

class SourceValidator {
public:
	bool Validate(vector<SourceToken>);
	bool ValidateProcedure(vector<SourceToken>, int&, vector<string>&, vector<string>&, map<string, float>&, map<string, string>&);
	bool ValidateStatement(vector<SourceToken>, int&, vector<string>&, vector<string>&, map<string, float>&, map<string, string>&);
	bool ValidateRead(vector<SourceToken>, int&, vector<string>&, vector<string>&);
	bool ValidatePrint(vector<SourceToken>, int&, vector<string>&);
	bool ValidateCall(vector<SourceToken>, int&, vector<string>&, map<string, string>&);
	bool ValidateIf(vector<SourceToken>, int&, vector<string>&, vector<string>&, map<string, float>&, map<string, string>&);
	bool ValidateWhile(vector<SourceToken>, int&, vector<string>&, vector<string>&, map<string, float>&, map<string, string>&);
	bool ValidateAssign(vector<SourceToken>, int&, vector<string>&, vector<string>&, map<string, float>&);
	bool ValidateExpression(vector<SourceToken>, int&, vector<string>&, map<string, float>&);
	bool ValidateArithmeticExpression(vector<SourceToken>, int&, vector<string>&, map<string, float>&);
	bool ValidateRelation(vector<SourceToken>, int&, vector<string>&, map<string, float>&);
};