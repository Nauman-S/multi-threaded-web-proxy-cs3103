#pragma once

#include <string>
#include <memory>

#include "../reference/Ref.h"
#include "../clause/AttrType.h"

class EntityRef
{
public:
	inline static const std::string kStmt = "stmt";
	inline static const std::string kRead = "read" ;
	inline static const std::string kPrint = "print";
	inline static const std::string kCall = "call";
	inline static const std::string kWhile = "while";
	inline static const std::string kIf = "if";
	inline static const std::string kAssign = "assign";
	inline static const std::string kVariable = "variable";
	inline static const std::string kConstant = "constant";
	inline static const std::string kProcedure = "procedure";

	std::shared_ptr<Ref> static EntityRef::CreateReference(std::string design_entity_, std::string synonym_);

	std::shared_ptr<Ref> static EntityRef::CreateReference(std::string design_entity_, std::string synonym_, AttrType attr_type);

};
