#pragma once

# include <vector>
# include "ProcedureIndex.h"
class ProcedureManager {
public:
	void addProcedure(ProcedureIndex&);

	std::vector<ProcedureIndex> getProcedures();

protected:
	std::vector<ProcedureIndex> procedures;
};