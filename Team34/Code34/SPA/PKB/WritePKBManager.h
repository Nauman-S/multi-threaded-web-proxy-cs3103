#pragma once
#include <memory>

#include "PKB.h"
#include "../Utils/type/TypeDef.h"

class WritePKBManager
{
public:
	static std::unique_ptr<WritePKBManager> GetInstance()
	{
		std::unique_ptr<WritePKBManager> manager(new WritePKBManager());
		return manager;
	}
    // APIs related to Variable entity
    void AddVariable(Variable var);

    // APIs related to Constant entity
    void AddConstant(Constant constant);

	// APIs related to Procedure entity
	void AddProcedure(Procedure proc);

	// APIs related to Statement
	void AddStatement(StmtNum stmt_num, RefType type);

	// APIs related to Parent relation
	void SetParent(StmtNum parent, StmtNum child);

	// APIs related to Parent* relation
	void SetParentS(StmtNum parent, StmtNum child);

	// APIs related to Uses relation
	void SetUses(StmtNum stmt_num, Variable var);
	void SetUses(Procedure proc_name, Variable var);

	//APIs related to Modifies relation
	void SetModifies(StmtNum stmt_num, Variable var);
	void SetModifies(Procedure proc_name, Variable var);
};