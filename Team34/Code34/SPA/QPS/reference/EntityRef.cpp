#include "EntityRef.h"

#include "..\reference\Ref.h"
#include "..\reference\StmtRef.h"
#include "..\reference\ReadRef.h"
#include "..\reference\PrintRef.h"
#include "..\reference\CallRef.h"
#include "..\reference\WhileRef.h"
#include "..\reference\IfRef.h"
#include "..\reference\AssignRef.h"
#include "..\reference\VarRef.h"
#include "..\reference\ConstRef.h"
#include "..\reference\ConstRef.h"
#include "..\reference\ProcRef.h"
#include "..\..\Utils\error\SyntaxError.h"

#include <string>
#include <memory>

std::shared_ptr<Ref> EntityRef::CreateReference(std::string design_entity_, std::string synonym_) {
	if (design_entity_.compare(EntityRef::kStmt) == 0) {
		return std::shared_ptr<StmtRef>(new StmtRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kRead) == 0) {
		return std::shared_ptr<ReadRef>(new ReadRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kPrint) == 0) {
		return std::shared_ptr<PrintRef>(new PrintRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kCall) == 0) {
		return std::shared_ptr<CallRef>(new CallRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kWhile) == 0) {
		return std::shared_ptr<WhileRef>(new WhileRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kIf) == 0) {
		return std::shared_ptr<IfRef>(new IfRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kAssign) == 0) {
		return std::shared_ptr<AssignRef>(new AssignRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kVariable) == 0) {
		return std::shared_ptr<VarRef>(new VarRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kConstant) == 0) {
		return std::shared_ptr<ConstRef>(new ConstRef(ValType::kSynonym, synonym_));
	} else if (design_entity_.compare(EntityRef::kProcedure) == 0) {
		return std::shared_ptr<ProcRef>(new ProcRef(ValType::kSynonym, synonym_));
	} else {
		throw SyntaxError("Illegal reference type!");
	}
}

std::shared_ptr<Ref> EntityRef::CreateReference(std::string design_entity_, std::string synonym_, AttrType attr_type) {
	if (design_entity_.compare(EntityRef::kStmt) == 0) {
		return std::shared_ptr<StmtRef>(new StmtRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kRead) == 0) {
		return std::shared_ptr<ReadRef>(new ReadRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kPrint) == 0) {
		return std::shared_ptr<PrintRef>(new PrintRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kCall) == 0) {
		return std::shared_ptr<CallRef>(new CallRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kWhile) == 0) {
		return std::shared_ptr<WhileRef>(new WhileRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kIf) == 0) {
		return std::shared_ptr<IfRef>(new IfRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kAssign) == 0) {
		return std::shared_ptr<AssignRef>(new AssignRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kVariable) == 0) {
		return std::shared_ptr<VarRef>(new VarRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kConstant) == 0) {
		return std::shared_ptr<ConstRef>(new ConstRef(ValType::kSynonym, synonym_, attr_type));
	} else if (design_entity_.compare(EntityRef::kProcedure) == 0) {
		return std::shared_ptr<ProcRef>(new ProcRef(ValType::kSynonym, synonym_, attr_type));
	} else {
		throw SyntaxError("Illegal reference type!");
	}
}
