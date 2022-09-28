#pragma once
#include <set>

#include "../../Utils/type/TypeDef.h"
using namespace std;

class ControlFlowNode {
public:
	void AddStmtNum(StmtNum);

	void AddOutgoingNode(shared_ptr<ControlFlowNode>);

	set<shared_ptr<ControlFlowNode>> GetOutgoingNodes();


protected:
	set<StmtNum> elements;
	set<shared_ptr<ControlFlowNode>> outgoing;
};