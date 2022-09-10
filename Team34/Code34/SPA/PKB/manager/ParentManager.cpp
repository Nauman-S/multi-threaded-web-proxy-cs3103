# include "ParentManager.h"

// Parent Relation methods
void ParentManager::SetParent(StmtNum parent, StmtNum child)
{
	// defensive checks
	assert(parent < child);
	if (child_to_parent_map_.find(child) != child_to_parent_map_.end())
	{
		// throw some error as relationship already exists
	}
	all_parent_relations_.push_back(std::make_pair(parent, child));
	parent_to_child_map_[parent].insert(child);
	child_to_parent_map_[child] = parent;
}

bool ParentManager::CheckParent(StmtNum child, StmtNum parent)
{
	return child_to_parent_map_[child] == parent;
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetChild(StmtNum parent)
{
	if (parent_to_child_map_.find(parent) == parent_to_child_map_.end())
	{
		return std::make_shared<std::unordered_set<StmtNum>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<StmtNum>>(parent_to_child_map_[parent]);
	}
}

StmtNum ParentManager::GetParent(StmtNum child)
{
	if (child_to_parent_map_.find(child) == child_to_parent_map_.end())
	{
		return NULL;
	}
	else
	{
		return child_to_parent_map_[child];
	}
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ParentManager::GetAllParentRelations()
{
	return std::make_shared<std::vector<std::pair<StmtNum, StmtNum>>>(all_parent_relations_);
}

// Parent* Relation methods
void ParentManager::SetParentS(StmtNum parent, StmtNum child)
{
	std::pair<StmtNum, StmtNum> pair = std::make_pair(parent, child);
	if (std::find(all_parent_s_relations_.begin(), all_parent_s_relations_.end(), pair) == all_parent_s_relations_.end())
	{
		all_parent_s_relations_.push_back(pair);
	}
}

bool ParentManager::CheckParentS(StmtNum parent, StmtNum child)
{
	auto iter = child_to_parent_map_.find(child);
	while (iter != child_to_parent_map_.end())
	{
		StmtNum next = child_to_parent_map_[child];
		if (next == parent)
		{
			return true;
		}
		iter = child_to_parent_map_.find(next);
	}
	return false;
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetAllChildren(StmtNum stmt)
{
	std::shared_ptr<std::unordered_set<StmtNum>> all_children = std::make_shared<std::unordered_set<StmtNum>>();
	std::queue<StmtNum> queue;
	queue.push(stmt);
	while (!queue.empty())
	{
		StmtNum parent = queue.front();
		queue.pop();
		auto iter = parent_to_child_map_.find(parent);
		if (iter == parent_to_child_map_.end())
		{
			continue;
		}
		std::unordered_set<StmtNum>& children = parent_to_child_map_[parent];
		for (auto iter = children.begin(); iter != children.end(); ++iter)
		{
			all_children->insert(*iter);
			queue.push(*iter);
		}
	}
	return all_children;
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetAllParents(StmtNum stmt)
{
	std::shared_ptr<std::unordered_set<StmtNum>> all_parents = std::make_shared<std::unordered_set<StmtNum>>();
	auto iter = child_to_parent_map_.find(stmt);
	while (iter != child_to_parent_map_.end())
	{
		StmtNum parent = child_to_parent_map_[stmt];
		all_parents->insert(parent);
		iter = child_to_parent_map_.find(parent);
	}
	return all_parents;
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ParentManager::GetAllParentSRelations()
{
	return std::make_shared<std::vector<std::pair<StmtNum, StmtNum>>>(all_parent_s_relations_);
}

