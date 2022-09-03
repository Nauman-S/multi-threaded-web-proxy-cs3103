# include "ProcedureManager.h"

void ProcedureManager::addProcedure(ProcedureIndex& proc) {
	procedures.push_back(proc);
}

std::vector<ProcedureIndex> ProcedureManager::getProcedures() {
	return procedures;
}