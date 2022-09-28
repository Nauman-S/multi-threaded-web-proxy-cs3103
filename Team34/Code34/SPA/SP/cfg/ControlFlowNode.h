#pragma once
#include <set>

#include "../../Utils/type/TypeDef.h"
using namespace std;

class ControlFlowNode {
public:
	void AddStmtNum(StmtNum);

	void AddOutgoingNode(ControlFlowNode);

	void AddIncomingNode(ControlFlowNode);

	set<ControlFlowNode> GetOutgoingNodes();

	set<ControlFlowNode> GetIncomingNodes();

protected:
	set<StmtNum> elements;
	set<ControlFlowNode> outgoing;
	set<ControlFlowNode> incoming;
};