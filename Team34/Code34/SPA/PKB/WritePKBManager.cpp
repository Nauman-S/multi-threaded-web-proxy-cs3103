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

void WritePKBManager::AddCallsStatement(Procedure proc, StmtNum stmt_num)
{
	pkb.statement_manager_.AddCallsStatement(proc, stmt_num);
}

void WritePKBManager::AddPrintStatement(Variable var, StmtNum stmt_num)
{
	pkb.statement_manager_.AddPrintStatement(var, stmt_num);
}

void WritePKBManager::AddReadStatement(Variable var, StmtNum stmt_num)
{
	pkb.statement_manager_.AddReadStatement(var, stmt_num);
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

// APIs related to Calls relation
void WritePKBManager::SetCalls(Procedure caller, Procedure callee)
{
	pkb.calls_manager_.SetCalls(caller, callee);
}

// APIs related to Calls* relation
void WritePKBManager::SetCallsT(Procedure caller, Procedure callee)
{
	pkb.calls_manager_.SetCallsT(caller, callee);
}

// APIs related to Next relation
void WritePKBManager::SetNext(StmtNum prev, StmtNum next)
{
	pkb.next_manager_.SetNext(prev, next);
}

// APIs related to Assign Pattern relation
void WritePKBManager::AddAssignPattern(StmtNum stmt_num, Expr expr)
{
	pkb.assign_pattern_manager_.AddPattern(stmt_num, expr);
}

// APIs related to If Pattern relation
void WritePKBManager::AddIfPattern(StmtNum stmt_num, Variable var)
{
	pkb.if_pattern_manager_.AddPattern(stmt_num, var);
}

// APIs related to While Pattern relation
void WritePKBManager::AddWhilePattern(StmtNum stmt_num, Variable var)
{
	pkb.while_pattern_manager_.AddPattern(stmt_num, var);
}
