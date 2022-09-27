#include "DesignExtractor.h"

#include <vector>
#include <memory>

#include "./tokenizer/SourceLexer.h"
#include "./tokenizer/SourceToken.h"

#include "./design_extractor/EntityExtractor.h"
#include "./design_extractor/UsesModifiesExtractor.h"
#include "./design_extractor/ParentsExtractor.h"
#include "./design_extractor/FollowsExtractor.h"
#include "./design_extractor/CallsExtractor.h"

#include "../PKB/WritePKBManager.h"

// Extracts all entities and relations from given root node of
// AST and stores into the PKB
void DesignExtractor::PopulatePKB(std::shared_ptr<ProgramNode> root) {
	EntityExtractor entity_extractor;
	UsesModifiesExtractor uses_modifies_extractor;
	ParentsExtractor parents_extractor;
	FollowsExtractor follows_extractor;
	CallsExtractor calls_extractor;

	root->Extract(entity_extractor);
	root->Extract(uses_modifies_extractor);
	root->Extract(parents_extractor);
	root->Extract(follows_extractor);
	root->Extract(calls_extractor);
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
