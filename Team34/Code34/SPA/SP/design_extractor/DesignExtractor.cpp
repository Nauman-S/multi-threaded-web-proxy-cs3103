#include "DesignExtractor.h"

#include <vector>
#include <memory>

#include "../SourceLexer.h"
#include "../SourceToken.h"

#include "EntityExtractor.h"
#include "UsesModifiesExtractor.h"

#include "../../PKB/WritePKBManager.h"

// Extracts all entities and relations from given root node of
// AST and stores into the PKB
void DesignExtractor::PopulatePKB(ProgramNode& root) {
	EntityExtractor entity_extractor;
	UsesModifiesExtractor uses_modifies_extractor;

	root.Extract(entity_extractor);
	root.Extract(uses_modifies_extractor);
}

void DesignExtractor::AddConstants(const std::string& source_filename) {
	std::shared_ptr<WritePKBManager> manager = WritePKBManager::GetInstance();

	SourceLexer lexer = SourceLexer(source_filename);
	std::vector<SourceToken> tokens = lexer.GetAllTokens();
	for (SourceToken t : tokens) {
		if (t.GetType() == SourceTokenType::kInteger) {
			int val = stoi(t.GetStringVal());
			manager->AddConstant(val);
		}
	}
}
