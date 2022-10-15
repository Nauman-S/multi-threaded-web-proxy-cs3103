#pragma once
#include <cassert>
#include <vector>
#include <unordered_set>
#include <memory>

#include "PKB.h"
#include "../Utils/type/TypeDef.h"
#include "../Utils/expression/ExprSpec.h"

class ReadPKBManager
{
public:
	static std::shared_ptr<ReadPKBManager> GetInstance()
	{
		std::shared_ptr<ReadPKBManager> manager(new ReadPKBManager());
		return manager;
	}

    // APIs related to Variable entity
    virtual bool IsVariable(Variable var);
	virtual const std::shared_ptr<std::unordered_set<Variable>> GetAllVariables();

    // APIs related to Constant entity
	virtual bool IsConstant(Constant constant);
	virtual const std::shared_ptr<std::unordered_set<Constant>> GetAllConstants();

	// APIs related to Procedure entity
	virtual bool IsProcedure(Procedure proc);
	virtual const std::shared_ptr<std::unordered_set<Procedure>> GetAllProcedures();

	// APIs related to Statements
	virtual std::shared_ptr<RefType> GetStatementType(StmtNum stmt_num);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetStatementsByType(RefType type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetCallsStatementFromProcedure(Procedure proc);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetPrintStatementFromVariable(Variable var);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetReadStatementFromVariable(Variable var);
	virtual std::shared_ptr<Procedure> GetCallsProcedureFromStatement(StmtNum stmt_num);
	virtual std::shared_ptr<Variable> GetPrintVariableFromStatement(StmtNum stmt_num);
	virtual std::shared_ptr<Variable> GetReadVariableFromStatement(StmtNum stmt_num);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Procedure>>> GetAllCallsStatementProcedurePairs();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllPrintStatementVariablePairs();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllReadStatementVariablePairs();

	// APIs related to Parent relation
	virtual bool CheckParent(StmtNum parent, StmtNum child);
	virtual bool IsParentStoreEmpty();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetChildrenFromStmt(StmtNum parent, RefType children_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetParentFromStmt(StmtNum child, RefType parent_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren(RefType children_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents(RefType parent_type);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations();

	// APIs related to Parent* relation
	virtual bool CheckParentT(StmtNum parent, StmtNum child);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildrenFromStmt(StmtNum stmt, RefType children_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllParentsFromStmt(StmtNum stmt, RefType parent_type);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentTRelations();

	// APIs related to Follows relation
	virtual bool CheckFollows(StmtNum left, StmtNum right);
	virtual bool IsFollowsStoreEmpty();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetSuccessorStmtFromStmt(StmtNum stmt, RefType successor_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetPredecessorStmtFromStmt(StmtNum stmt, RefType predecessor_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmts(RefType successor_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmts(RefType predecessor_type);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations();


	// APIs relation to Follows* relation
	virtual bool CheckFollowsT(StmtNum left, StmtNum right);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmtsFromStmt(StmtNum stmt, RefType successor_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmtsFromStmt(StmtNum stmt, RefType predecessor_type);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsTRelations();

	// APIs related to Uses relation
	virtual bool CheckUses(StmtNum stmt_num, Variable var);
	virtual bool CheckUses(Procedure proc_name, Variable var);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByStmtNum(StmtNum stmt_num);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByProcName(Procedure proc_name);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetUsesStmtNumByVar(Variable var, RefType stmt_type);
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetUsesProcNameByVar(Variable var);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllUsesStatements(RefType stmt_type);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetAllUsesSVariables();
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetAllUsesProcedures();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVUses();
	virtual std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVUses();
	
	// APIs related to Modifies relation
	virtual bool CheckModifies(StmtNum stmt_num, Variable var);
	virtual bool CheckModifies(Procedure proc_name, Variable var);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByStmtNum(StmtNum stmt_num);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByProcName(Procedure proc_name);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetModifiesStmtNumByVar(Variable var, RefType stmt_type);
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetModifiesProcNameByVar(Variable var);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllModifiesStatements(RefType stmt_type);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetAllModifiesSVariables();
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetAllModifiesProcedures();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies();
	virtual std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies();

	// APIs related to Calls relation
	virtual bool CheckCalls(Procedure caller, Procedure callee);
	virtual bool IsCallsStoreEmpty();
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetCalleeFromCaller(Procedure caller);
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetCallerFromCallee(Procedure callee);
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetAllCallers();
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetAllCallees();
	virtual std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> GetAllCallsRelations();

	// APIs related to Calls* relation
	virtual bool CheckCallsT(Procedure caller, Procedure callee);
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetAllCalleeFromCaller(Procedure caller);
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetAllCallerFromCallee(Procedure callee);
	virtual std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> GetAllCallsTRelations();

	// APIs related to Next relation
	virtual bool CheckNext(StmtNum prev, StmtNum next);
	virtual bool IsNextStoreEmpty();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetNextStmtsFromStmt(StmtNum stmt, RefType next_stmt_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetPrevStmtsFromStmt(StmtNum stmt, RefType prev_stmt_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllNextStmts(RefType next_stmt_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPrevStmts(RefType prev_stmt_type);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllNextRelations();

	// APIs related to Next* relation
	virtual bool CheckNextT(StmtNum prev, StmtNum next);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllNextStmtsFromStmt(StmtNum stmt, RefType next_stmt_type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPrevStmtsFromStmt(StmtNum stmt, RefType prev_stmt_type);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllNextTRelations();

	// APIs related to Assign Pattern relation
	virtual std::shared_ptr<std::unordered_set<StmtNum>> FilterByAssignPatternMatch(std::shared_ptr<ExprSpec> expr);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> FilterByAssignPatternMatch(Variable var, std::shared_ptr<ExprSpec> expr);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAssignPatternMatch(std::shared_ptr<ExprSpec> expr);

	// APIs related to If Pattern relation
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllIfPatternStatmentsFromVar(Variable var);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllIfPatternStatements();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllIfPatterns();

	// APIs related to While Pattern relation
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllWhilePatternStatmentsFromVar(Variable var);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllWhilePatternStatements();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllWhilePatterns();
private:
	virtual std::shared_ptr<std::unordered_set<StmtNum>> FilterStmtSetByType(std::shared_ptr<std::unordered_set<StmtNum>> stmts, RefType stmt_type);
};