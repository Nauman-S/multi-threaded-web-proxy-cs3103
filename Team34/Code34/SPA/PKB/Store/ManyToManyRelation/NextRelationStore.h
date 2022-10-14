#pragma once

#include "ManyToManyTransitiveRelationStore.h"
#include "../../../Utils/type/TypeDef.h"

class NextRelationStore : public ManyToManyTransitiveRelationStore<StmtNum>
{
public:
	void SetCodeBlock(StmtNum start, StmtNum end);
	void SetOptimisedCFGEdge(StmtNum prev_start, StmtNum next_start);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllTransitiveRelations();
	void Clear();
private:
	void OptimisedCFGTraversal(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations);
	void PopulateNextTPairsWithinBlock(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations,
		StmtNum code_block_start, StmtNum code_block_end);
	void PopulateNextTPairsBetweenSameBlock(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations,
		StmtNum code_block_start, StmtNum code_block_end);
	void PopulateNextTPairsBetweenBlocks(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations,
		StmtNum code_block_start, StmtNum code_block_end, StmtNum next_block_start, StmtNum next_block_end);

	std::unordered_map<StmtNum, StmtNum> code_block_map_;
	std::unordered_set<StmtNum> code_block_set_;
	std::unordered_map<StmtNum, std::unordered_set<StmtNum>> optimised_cfg_;
};
