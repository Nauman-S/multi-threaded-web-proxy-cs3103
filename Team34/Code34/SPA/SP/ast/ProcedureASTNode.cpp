#include "ProcedureASTNode.h"

using namespace std;

Procedure ProcedureASTNode::GetProc() const {
	return proc;
}

std::vector<std::shared_ptr<StatementASTNode>> ProcedureASTNode::GetChildren() const {
	return children;
}

void ProcedureASTNode::SetProc(Procedure& p) {
	proc = p;
}

void ProcedureASTNode::SetChildren(std::vector<std::shared_ptr<StatementASTNode>>& chd) {
	children = chd;
}

void ProcedureASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractProcedureNode(*this);
}

string ProcedureASTNode::Stringify() {
	string tp = "Procedure";
	string children_s = "";
	for (shared_ptr<StatementASTNode> node : children) {
		children_s += node->Stringify();
	}
	return tp + children_s;
}
