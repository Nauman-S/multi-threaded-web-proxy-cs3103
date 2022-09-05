#include "CallStatementASTNode.h"

using namespace std;

void CallStatementASTNode::setProcedure(ProcedureIndex& p) {
	proc = p;
}

ProcedureIndex CallStatementASTNode::getProcedure() {
	return proc;
}

void CallStatementASTNode::Extract(NodeExtractor& extractor) {

}

