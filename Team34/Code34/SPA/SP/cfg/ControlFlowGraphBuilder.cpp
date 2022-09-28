#include "ControlFlowGraphBuilder.h"

using namespace std;

ControlFlowNode ControlFlowGraphBuilder::GenerateCFG(ProcedureASTNode& proc) {
	shared_ptr<ControlFlowNode> root (new ControlFlowNode());

	shared_ptr<ControlFlowNode>* cur = root;
	for (shared_ptr<StatementASTNode> node : proc.GetChildren()) {
		StatementHandler(cur, &node)
	}
}

void ControlFlowGraphBuilder::StatementHandler(shared_ptr<ControlFlowNode>* cur, shared_ptr<StatementASTNode>& node) {
	if (node.GetTypeVal() == "assign" || node.GetTypeVal() == "acall" || node.GetTypeVal() == "aread" || node.GetTypeVal() == "aprint") {
		SingleHandler(cur, &node);
	}
	else if (node.GetTypeVal() == "awhile") {
		WhileHandler(cur, node)
	}
	else if (node.GetTypeVal() == "aif") {
		IfHandler(cur, node)
	}
}

void ControlFlowGraphBuilder::SingleHandler(shared_ptr<ControlFlowNode>* cur, shared_ptr<StatementASTNode>& node) {
	cur->AddStmtNum(node.GetLineIndex());
}

void ControlFlowGraphBuilder::WhileHandler(shared_ptr<ControlFlowNode>* cur, shared_ptr<StatementASTNode>& node) {
	shared_ptr<ControlFlowNode> w_node (new ControlFlowNode());
	cur->AddOutgoingNode(w_node);
	// w_node->AddOutgoingNode(*cur) ×îºó
	cur = &w_node

	for (shared_ptr<StatementASTNode> n : node.GetChildren()) {
		StatementHandler(cur, n)
	}
	
}