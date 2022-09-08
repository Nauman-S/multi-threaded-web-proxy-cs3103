#pragma once

#include<string>
class EntityRef
{
public:
	static const std::string kStmt;
	static const std::string kRead;
	static const std::string kPrint;
	static const std::string kCall;
	static const std::string kWhile;
	static const std::string kIf;
	static const std::string kAssign;
	static const std::string kVariable;
	static const std::string kConstant;
	static const std::string kProcedure;
private:
};

const std::string kStmt = "STMT";
const std::string kRead = "READ";
const std::string kPrint = "PRINT";
const std::string kCall = "CALL";
const std::string kWhile = "WHILE";
const std::string kIf = "IF";
const std::string kAssign = "ASSIGN";
const std::string kVariable = "VARIABLE";
const std::string kConstant = "CONSTANT";
const std::string kProcedure = "PROCEDURE";