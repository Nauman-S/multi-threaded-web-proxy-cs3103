#include "RefFactory.h"

#include <memory>
#include <optional>
#include <string>

#include "AssignRef.h"
#include "CallRef.h"
#include "ConstRef.h"
#include "IfRef.h"
#include "PrintRef.h"
#include "ProcRef.h"
#include "Ref.h"
#include "ReadRef.h"
#include "VarRef.h"
#include "WhileRef.h"
#include "EntityRef.h"

std::optional<std::shared_ptr<Ref>> RefFactory::CreateReference(std::string design_entity_, std::string synonym_) {

	if (design_entity_.compare(EntityRef::kStmt) == 0) {
		return std::shared_ptr<StmtRef>(new StmtRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kRead) == 0) {
		return std::shared_ptr<ReadRef>(new ReadRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kPrint) == 0) {
		return std::shared_ptr<PrintRef>(new PrintRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kCall) == 0) {
		return std::shared_ptr<CallRef>(new CallRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kWhile) == 0) {
		return std::shared_ptr<WhileRef>(new WhileRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kIf) == 0) {
		return std::shared_ptr<IfRef>(new IfRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kAssign) == 0) {
		return std::shared_ptr<AssignRef>(new AssignRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kVariable) == 0) {
		return std::shared_ptr<VarRef>(new VarRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kConstant) == 0) {
		return std::shared_ptr<ConstRef>(new ConstRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare(EntityRef::kProcedure) == 0) {
		return std::shared_ptr<ProcRef>(new ProcRef(ValType::kSynonym, synonym_));
	}

	return {};
}