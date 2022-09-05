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

	//APIs related to Statement
	void AddStatement(StmtNum stmt_num, RefType type);

	// APIs related to Uses relation
	void SetUses(int stmt_num, std::string var);
	void SetUses(std::string proc_name, std::string var);

	//APIs related to Modifies relation
	void SetModifies(int stmt_num, std::string var);
	void SetModifies(std::string proc_name, std::string var);
};