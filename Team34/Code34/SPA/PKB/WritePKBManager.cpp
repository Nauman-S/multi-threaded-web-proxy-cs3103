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
void WritePKBManager::SetParent(StmtNum parent, StmtNum child)
{
	return pkb.parent_manager_.SetParent(parent, child);
}

// APIs related to Parent* relation
void WritePKBManager::SetParentT(StmtNum parent, StmtNum child)
{
	return pkb.parent_manager_.SetParentT(parent, child);
}

void WritePKBManager::SetFollows(StmtNum left, StmtNum right)
{
	return pkb.follows_manager_.SetFollows(left, right);
}

void WritePKBManager::SetFollowsT(StmtNum left, StmtNum right)
{
	return pkb.follows_manager_.SetFollowsT(left, right);
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

void WritePKBManager::AddAssignPattern(StmtNum stmt_num, Variable var, std::string expr)
{
	pkb.pattern_manager_.AddAssignPattern(stmt_num, var, expr);
}
