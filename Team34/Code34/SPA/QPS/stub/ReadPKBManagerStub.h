#pragma once

#include <memory>
#include <unordered_set>
#include <vector>
#include <utility>

#include "../../Utils/type/TypeDef.h"
#include "../../PKB/ReadPKBManager.h"

class ReadPKBManagerStub : public ReadPKBManager
{
	/*
		This stub is made with the following SIMPLE source program
		For testing calls and with procName:
		procedure Foo1 {
		7	call bar;
		}

		procedure bar {
			
		8	call Nine;
		9	call Nine;
		}

		procedure Nine {
		}

		For testing ModifiesP:
		procedure func1 {
			read x;
		}

		For testing UsesP:
		procedure func2 {
			print y;
		}

		For testing UsesS and ModifiesS
		5  x = y + 1;  

		

		For testing Follows(T), Parent(T), 
		procedure main {
		1  while(x < 2) {
		2    x = y + 2
		3    if(x < 2) {
		4	    x = z + 2
			 } else {
		5	    x = z - 2
			 }
		6	 z = 5
		   }
		}

		Parent(1,2), Parent(1,3), Parent(1,6), Parent(3,4), Parent(3,5)
		ParentT(1,2), ParentT(1,3), ParentT(1,6), ParentT(3,4), ParentT(3,5), ParentT(1, 4), ParentT(1,5)
		Follows(2,3), Follows(3,6),
		FollowsT(2,3), FollowsT(3,6), FollowsT(2,6)
	
	*/

	// APIs related to Variable Entity
	virtual const std::shared_ptr<std::unordered_set<Variable>> GetAllVariables();
	virtual bool IsVariable(Variable var);

	// APIs related to Procedure entity
	virtual bool IsProcedure(Procedure proc);
	virtual const std::shared_ptr<std::unordered_set<Procedure>> GetAllProcedures();

	// APIs related to Statements
	virtual std::shared_ptr<RefType> GetStatementType(StmtNum stmt_num);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetStatementsByType(RefType type);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetCallsStatementFromProcedure(Procedure proc);

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

	// APIs related to Uses relation
	bool CheckUses(StmtNum stmt_num, Variable var) override;
	bool CheckUses(Procedure proc_name, Variable var) override;
	std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByStmtNum(StmtNum stmt_num) override;
	std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByProcName(Procedure proc_name) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetUsesStmtNumByVar(Variable var, RefType stmt_type) override;
	std::shared_ptr<std::unordered_set<Procedure>> GetUsesProcNameByVar(Variable var) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllUsesStatements(RefType stmt_type) override;
	std::shared_ptr<std::unordered_set<Procedure>> GetAllUsesProcedures() override;
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVUses() override;
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVUses() override;

	// APIs related to Modifies relation
	bool CheckModifies(StmtNum stmt_num, Variable var) override;
	bool CheckModifies(Procedure proc_name, Variable var) override;
	std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByStmtNum(StmtNum stmt_num) override;
	std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByProcName(Procedure proc_name) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetModifiesStmtNumByVar(Variable , RefType stmt_type) override;
	std::shared_ptr<std::unordered_set<Procedure>> GetModifiesProcNameByVar(Variable var) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllModifiesStatements(RefType stmt_type) override;
	std::shared_ptr<std::unordered_set<Procedure>> GetAllModifiesProcedures() override;
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies() override;
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies() override;

	// APIs related to Follows relation
	bool CheckFollows(StmtNum left, StmtNum right) override;
	bool IsFollowsStoreEmpty() override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetSuccessorStmtFromStmt(StmtNum stmt, RefType successor_type) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetPredecessorStmtFromStmt(StmtNum stmt, RefType predecessor_type) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmts(RefType successor_type) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmts(RefType predecessor_type) override;
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations() override;

	// APIs relation to Follows* relation
	bool CheckFollowsT(StmtNum left, StmtNum right) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmtsFromStmt(StmtNum stmt, RefType successor_type) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmtsFromStmt(StmtNum stmt, RefType predecessor_type) override;
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsTRelations() override;

	// APIs related to Parent relation
	bool CheckParent(StmtNum parent, StmtNum child) override;
	bool IsParentStoreEmpty() override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetChildrenFromStmt(StmtNum parent, RefType children_type) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetParentFromStmt(StmtNum child, RefType parent_type) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren(RefType children_type) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents(RefType parent_type) override;
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations() override;

	// APIs related to Parent* relation
	bool CheckParentT(StmtNum parent, StmtNum child) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildrenFromStmt(StmtNum stmt, RefType children_type) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParentsFromStmt(StmtNum stmt, RefType parent_type) override;
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentTRelations() override;
};