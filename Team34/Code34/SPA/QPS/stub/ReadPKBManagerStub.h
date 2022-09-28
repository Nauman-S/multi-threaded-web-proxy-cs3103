#pragma once

#include <memory>
#include <unordered_set>

#include "../../Utils/type/TypeDef.h"
#include "../../PKB/ReadPKBManager.h"

class ReadPKBManagerStub : public ReadPKBManager
{
	/*
		This stub is made with the following SIMPLE source program

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

		

		For testing Follows(T), Parent(T)

		1  while(x < 2) {
		2    x = y + 2
		3    if(x < 2) {
		4	    x = z + 2
			 } else {
		5	    x = z - 2
			 }
		6	 z = 5
		   }

		Parent(1,2), Parent(1,3), Parent(1,6), Parent(3,4), Parent(3,5)
		ParentT(1,2), ParentT(1,3), ParentT(1,6), ParentT(3,4), ParentT(3,5), ParentT(1, 4), ParentT(1,5)
		Follows(2,3), Follows(3,6),
		FollowsT(2,3), FollowsT(3,6), FollowsT(2,6)
	
	*/
	// APIs related to Statements
	std::shared_ptr<RefType> GetStatementType(StmtNum stmt_num);

	// APIs related to Uses relation
	bool CheckUses(StmtNum stmt_num, Variable var) override;
	bool CheckUses(Procedure proc_name, Variable var) override;
	std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByStmtNum(StmtNum stmt_num) override;
	std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByProcName(Procedure proc_name) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetUsesStmtNumByVar(Variable var) override;
	std::shared_ptr<std::unordered_set<Procedure>> GetUsesProcNameByVar(Variable var) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllUsesStatements() override;
	std::shared_ptr<std::unordered_set<Procedure>> GetAllUsesProcedures() override;
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVUses() override;
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVUses() override;

	// APIs related to Modifies relation
	bool CheckModifies(StmtNum stmt_num, Variable var) override;
	bool CheckModifies(Procedure proc_name, Variable var) override;
	std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByStmtNum(StmtNum stmt_num) override;
	std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByProcName(Procedure proc_name) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetModifiesStmtNumByVar(Variable var) override;
	std::shared_ptr<std::unordered_set<Procedure>> GetModifiesProcNameByVar(Variable var) override;
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllModifiesStatements() override;
	std::shared_ptr<std::unordered_set<Procedure>> GetAllModifiesProcedures() override;
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies() override;
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies() override;

	// APIs related to Follows relation
	virtual bool CheckFollows(StmtNum left, StmtNum right) override;
	virtual bool IsFollowsStoreEmpty() override;
	virtual StmtNum GetSuccessorStmtFromStmt(StmtNum stmt) override;
	virtual StmtNum GetPredecessorStmtFromStmt(StmtNum stmt) override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmts() override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmts() override;
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations() override;

	// APIs relation to Follows* relation
	virtual bool CheckFollowsT(StmtNum left, StmtNum right) override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmtsFromStmt(StmtNum stmt) override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmtsFromStmt(StmtNum stmt) override;
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsTRelations() override;

	// APIs related to Parent relation
	virtual bool CheckParent(StmtNum parent, StmtNum child) override;
	virtual bool IsParentStoreEmpty() override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetChildrenFromStmt(StmtNum parent, RefType children_type) override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetParentFromStmt(StmtNum child, RefType parent_type) override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren() override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents() override;
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations() override;

	// APIs related to Parent* relation
	virtual bool CheckParentT(StmtNum parent, StmtNum child) override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildrenFromStmt(StmtNum stmt, RefType children_type) override;
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllParentsFromStmt(StmtNum stmt, RefType parent_type) override;
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentTRelations() override;
};