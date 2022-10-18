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
    std::shared_ptr<WritePKBManager> write_manager = WritePKBManager::GetInstance();

    EntityExtractor entity_extractor(write_manager);
    UsesModifiesExtractor uses_modifies_extractor(write_manager);
    ParentsExtractor parents_extractor(write_manager);
    FollowsExtractor follows_extractor(write_manager);
    CallsExtractor calls_extractor(write_manager);
    NextExtractor next_extractor(write_manager);

    root->Extract(entity_extractor);
    root->Extract(uses_modifies_extractor);
    root->Extract(parents_extractor);
    root->Extract(follows_extractor);
    root->Extract(calls_extractor);
    root->Extract(next_extractor);
}
