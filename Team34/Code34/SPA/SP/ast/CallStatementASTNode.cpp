#include "CallStatementASTNode.h"

using namespace std;

void CallStatementASTNode::SetProcedure(Procedure& p) {
	proc = p;
}

Procedure CallStatementASTNode::GetProcedure() const {
	return proc;
}

void CallStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractCallNode(*this);
}

string CallStatementASTNode::Stringify() {
	string tp = "Call";
	string proc_s = proc;
	return tp + proc_s;
}