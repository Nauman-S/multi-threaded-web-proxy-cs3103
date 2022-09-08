#include "WritePKBManager.h"

// APIs related to Variable entity
void WritePKBManager::AddVariable(Variable var)
{
    pkb.variable_manager_.AddEntity(var);
}

// APIs related to Constant entity
void WritePKBManager::AddConstant(Constant constant)
{
	pkb.constant_manager_.AddEntity(constant);
}

// APIs related to Procedure entity
void WritePKBManager::AddProcedure(Procedure proc)
{
	pkb.procedure_manager_.AddEntity(proc);
}

// APIs related to Statement
void WritePKBManager::AddStatement(StmtNum stmt_num, RefType type)
{
	pkb.statement_manager_.AddStatement(stmt_num, type);
}

// APIs related to Parent relation
void WritePKBManager::SetParent(StmtNum child, StmtNum parent)
{
	return pkb.parent_manager_.SetParent(child, parent);
}

// APIs related to Parent* relation
void WritePKBManager::SetParentS(StmtNum child, StmtNum parent)
{
	return pkb.parent_manager_.SetParentS(child, parent);
}

// APIs related to Uses relation
void WritePKBManager::SetUses(StmtNum stmt_num, Variable var)
{
	pkb.uses_manager_.SetUses(stmt_num, var);
}

void WritePKBManager::SetUses(Procedure proc_name, Variable var)
{
	pkb.uses_manager_.SetUses(proc_name, var);
}

//APIs related to Modifies relation
void WritePKBManager::SetModifies(StmtNum stmt_num, Variable var)
{
	pkb.modifies_manager_.SetModifies(stmt_num, var);
}

void WritePKBManager::SetModifies(Procedure proc_name, Variable var)
{
	pkb.modifies_manager_.SetModifies(proc_name, var);
}