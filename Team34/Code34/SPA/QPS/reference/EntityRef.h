#pragma once

#include "..\reference\Ref.h"

#include<string>
#include <memory>

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

	std::shared_ptr<Ref> static EntityRef::CreateReference(std::string design_entity_, std::string synonym_);
private:
};
