#include "ControlFlowNode.h"

using namepace std;

void ControlFlowNode::AddStmtNum(StmtNum num) {
	elements.insert(num);
}

void ControlFlowNode::AddOutgoingNode(ControlFlowNode node) {
	outgoing.insert(node);
}

void ControlFlowNode::AddIncomingNode(ControlFlowNode node) {
	incoming.insert(node);
}

set<ControlFlowNode> ControlFlowNode::GetIncomingNodes() {
	return incoming;
}

set<ControlFlowNode> ControlFlowNode::GetOutgoingNodes() {
	return outgoing;
}