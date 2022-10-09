#include "WritePKBManagerStub.h"

void WritePKBManagerStub::SetCodeBlock(StmtNum start, StmtNum end) {
	this->set_code_blocks_.insert(std::make_pair(start, end));
}

bool WritePKBManagerStub::CheckCodeBlockSet(StmtNum start, StmtNum end) {
	std::pair<StmtNum, StmtNum> pair = std::make_pair(start, end);
	return this->set_code_blocks_.find(pair) != this->set_code_blocks_.end();
}

void WritePKBManagerStub::SetOptimisedCFGEdge(StmtNum start, StmtNum next) {
	this->set_optimised_edges.insert(std::make_pair(start, next));
}

bool WritePKBManagerStub::CheckOptimisedEdgeSet(StmtNum start, StmtNum next) {
	std::pair<StmtNum, StmtNum> pair = std::make_pair(start, next);
	return this->set_optimised_edges.find(pair) != this->set_optimised_edges.end();
}

void WritePKBManagerStub::ClearAll() {
	this->set_code_blocks_.clear();
	this->set_optimised_edges.clear();
}
