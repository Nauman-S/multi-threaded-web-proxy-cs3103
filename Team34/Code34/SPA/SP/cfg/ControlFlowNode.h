#pragma once
#include <set>
#include <memory>
#include "../../Utils/type/TypeDef.h"
using namespace std;

class ControlFlowNode {
public:
	void AddStmtNum(StmtNum);

	set<StmtNum> GetElements();

	void AddOutgoingNode(shared_ptr<ControlFlowNode>);

	set<shared_ptr<ControlFlowNode>> GetOutgoingNodes();

	bool isEmpty();

protected:
	set<StmtNum> elements;
	set<shared_ptr<ControlFlowNode>> outgoing;
	bool flag = true;
};