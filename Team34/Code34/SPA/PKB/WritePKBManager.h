#pragma once
#include <memory>

#include "PKB.h"
#include "../Utils/type/TypeDef.h"
#include "../Utils/expression/Expr.h"

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
	void AddCallsStatement(Procedure proc, StmtNum stmt_num);
	void AddPrintStatement(Variable var, StmtNum stmt_num);
	void AddReadStatement(Variable var, StmtNum stmt_num);

	// APIs related to Parent relation
	void SetParent(StmtNum parent, StmtNum child);

	// APIs related to Parent* relation
	void SetParentT(StmtNum parent, StmtNum child);

	// APIs related to Follows relation
	void SetFollows(StmtNum left, StmtNum right);

	// APIs related to Follows* relation
	void SetFollowsT(StmtNum left, StmtNum right);

	// APIs related to Uses relation
	void SetUses(StmtNum stmt_num, Variable var);
	void SetUses(Procedure proc_name, Variable var);

	// APIs related to Modifies relation
	void SetModifies(StmtNum stmt_num, Variable var);
	void SetModifies(Procedure proc_name, Variable var);

	// APIs related to Calls relation
	void SetCalls(Procedure caller, Procedure callee);

	// APIs related to Calls* relation
	void SetCallsT(Procedure caller, Procedure callee);

	// APIs related to Next relation
	void SetNext(StmtNum prev, StmtNum next);
	virtual void SetCodeBlock(StmtNum start, StmtNum end);
	virtual void SetOptimisedCFGEdge(StmtNum prev_start, StmtNum next_start);

	// APIs related to Assign Pattern relation
	void AddAssignPattern(StmtNum stmt_num, Expr expr);

	// APIs related to If Pattern relation
	void AddIfPattern(StmtNum stmt_num, Variable var);

	// APIs related to While Pattern relation
	void AddWhilePattern(StmtNum stmt_num, Variable var);

	// Utility APIs
	void ResetPKB();
};