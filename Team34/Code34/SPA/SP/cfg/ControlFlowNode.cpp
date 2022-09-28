#include "ControlFlowNode.h"

using namepace std;

void ControlFlowNode::AddStmtNum(StmtNum num) {
	elements.insert(num);
}

void ControlFlowNode::AddOutgoingNode(shared_ptr<ControlFlowNode> node) {
	outgoing.insert(node);
}

set<shared_ptr<ControlFlowNode>> ControlFlowNode::GetOutgoingNodes() {
	return outgoing;
}