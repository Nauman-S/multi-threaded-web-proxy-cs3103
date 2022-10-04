#include "DesignExtractor.h"

#include <vector>
#include <memory>

#include "./design_extractor/EntityExtractor.h"
#include "./design_extractor/UsesModifiesExtractor.h"
#include "./design_extractor/ParentsExtractor.h"
#include "./design_extractor/FollowsExtractor.h"
#include "./design_extractor/CallsExtractor.h"
#include "./design_extractor/NextExtractor.h"

#include "../PKB/WritePKBManager.h"

// Extracts all entities and relations from given root node of
// AST and stores into the PKB
void DesignExtractor::PopulatePKB(std::shared_ptr<ProgramNode> root) {
	EntityExtractor entity_extractor;
	UsesModifiesExtractor uses_modifies_extractor;
	ParentsExtractor parents_extractor;
	FollowsExtractor follows_extractor;
	CallsExtractor calls_extractor;
	NextExtractor next_extractor;

	root->Extract(entity_extractor);
	root->Extract(uses_modifies_extractor);
	root->Extract(parents_extractor);
	root->Extract(follows_extractor);
	root->Extract(calls_extractor);
	root->Extract(next_extractor);
}
