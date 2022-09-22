#include "ProgramNode.h"

using namespace std;

std::vector<shared_ptr<ProcedureASTNode>> ProgramNode::GetChildren() {
	return children;
}

void ProgramNode::SetChildren(std::vector<std::shared_ptr<ProcedureASTNode>> c) {
	children = c;
}

void ProgramNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractProgramNode(*this);
}
