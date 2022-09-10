#pragma once

#include<string>
class EntityRef
{
public:
	inline static const std::string kStmt = "STMT";
	inline static const std::string kRead = "READ" ;
	inline static const std::string kPrint = "PRINT";
	inline static const std::string kCall = "CALL";
	inline static const std::string kWhile = "WHILE";
	inline static const std::string kIf = "IF";
	inline static const std::string kAssign = "ASSIGN";
	inline static const std::string kVariable = "VARIABLE";
	inline static const std::string kConstant = "CONSTANT";
	inline static const std::string kProcedure = "PROCEDURE";
private:
};
