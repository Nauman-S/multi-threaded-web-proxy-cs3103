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

std::optional<std::shared_ptr<Ref>> RefFactory::CreateReference(std::string design_entity_, std::string synonym_) {

	if (design_entity_.compare("STMT") == 0) {
		return std::shared_ptr<StmtRef>(new StmtRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("READ") == 0) {
		return std::shared_ptr<ReadRef>(new ReadRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("PRINT") == 0) {
		return std::shared_ptr<PrintRef>(new PrintRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("CALL") == 0) {
		return std::shared_ptr<CallRef>(new CallRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("WHILE") == 0) {
		return std::shared_ptr<WhileRef>(new WhileRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("IF") == 0) {
		return std::shared_ptr<IfRef>(new IfRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("ASSIGN") == 0) {
		return std::shared_ptr<AssignRef>(new AssignRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("VARIABLE") == 0) {
		return std::shared_ptr<VarRef>(new VarRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("CONSTANT") == 0) {
		return std::shared_ptr<ConstRef>(new ConstRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("PROCEDURE") == 0) {
		return std::shared_ptr<ProcRef>(new ProcRef(ValType::kSynonym, synonym_));
	}

	return {};
}