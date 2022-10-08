#include "NextRelationStore.h"


void NextRelationStore::SetCodeBlock(StmtNum start, StmtNum end)
{

	if (code_block_map_.find(start) == code_block_map_.end())
	{
		code_block_map_[start] = end;
		code_block_set_.insert(start);
	}
}

void NextRelationStore::SetOptimisedCFGEdge(StmtNum prev_start, StmtNum next_start)
{
	optimised_cfg_[prev_start].insert(next_start);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> NextRelationStore::GetAllTransitiveRelations()
{
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations = std::make_shared<std::vector<std::pair<StmtNum, StmtNum>>>();
	OptimisedCFGTraversal(all_transitive_relations);
	return all_transitive_relations;
}

void NextRelationStore::OptimisedCFGTraversal(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations)
{
	for (auto node = code_block_set_.begin(); node != code_block_set_.end(); ++node)
	{
		StmtNum code_block_start = *node;
		StmtNum code_block_end = code_block_map_[code_block_start];
		std::unordered_set<StmtNum> visited;
		std::queue<StmtNum> queue;
		PopulateNextTPairsWithinBlock(all_transitive_relations, code_block_start, code_block_end);
		queue.push(code_block_start);
		while (!queue.empty())
		{
			StmtNum ptr = queue.front();
			queue.pop();
			if (code_block_map_.find(ptr) == code_block_map_.end()) continue;
			std::unordered_set<StmtNum>& next_nodes = optimised_cfg_[ptr];
			for (auto iter = next_nodes.begin(); iter != next_nodes.end(); ++iter)
			{
				if (visited.find(*iter) != visited.end()) continue;
				StmtNum next_block_start = *iter;
				StmtNum next_block_end = code_block_map_[*iter];
				if (code_block_start == next_block_start)
				{
					PopulateNextTPairsBetweenSameBlock(all_transitive_relations, code_block_start, code_block_end);
				}
				else
				{
					PopulateNextTPairsBetweenBlocks(all_transitive_relations, code_block_start, code_block_end,
						next_block_start, next_block_end);
				}
				visited.insert(next_block_start);
				queue.push(next_block_start);
			}
		}
	}
}

void NextRelationStore::PopulateNextTPairsWithinBlock(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations,
	StmtNum code_block_start, StmtNum code_block_end)
{
	for (StmtNum lhs = code_block_start; lhs < code_block_end; ++lhs)
	{
		for (StmtNum rhs = lhs + 1; rhs <= code_block_end; ++rhs)
		{
			all_transitive_relations->push_back(std::make_pair(lhs, rhs));
		}
	}
}

void NextRelationStore::PopulateNextTPairsBetweenSameBlock(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations,
	StmtNum code_block_start, StmtNum code_block_end)
{
	for (StmtNum lhs = code_block_end; lhs >= code_block_start; --lhs)
	{
		for (StmtNum rhs = lhs; rhs >= code_block_start; --rhs)
		{
			all_transitive_relations->push_back(std::make_pair(lhs, rhs));
		}
	}
}

void NextRelationStore::PopulateNextTPairsBetweenBlocks(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations,
	StmtNum code_block_start, StmtNum code_block_end, StmtNum next_block_start, StmtNum next_block_end)
{
	for (StmtNum lhs = code_block_start; lhs <= code_block_end; ++lhs)
	{
		for (StmtNum rhs = next_block_start; rhs <= next_block_end; ++rhs)
		{
			all_transitive_relations->push_back(std::make_pair(lhs, rhs));
		}
	}
}