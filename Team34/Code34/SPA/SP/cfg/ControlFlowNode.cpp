#include "ControlFlowNode.h"

using namespace std;

void ControlFlowNode::AddStmtNum(StmtNum num) {
	flag = false;
	elements.insert(num);
}

set<StmtNum> ControlFlowNode::GetElements() {
	return elements;
}

void ControlFlowNode::AddOutgoingNode(shared_ptr<ControlFlowNode> node) {
	outgoing.insert(node);
}

set<shared_ptr<ControlFlowNode>> ControlFlowNode::GetOutgoingNodes() {
	return outgoing;
}

bool ControlFlowNode::isEmpty() {
	return flag;
}

