#include "ProcedureIndex.h"

using namespace std;

void ProcedureIndex::SetName(std::string n) {
	procName = n;
}

std::string ProcedureIndex::GetName() {
	return procName;
}