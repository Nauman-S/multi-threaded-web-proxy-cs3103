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
	bool CheckUses(Procedure proc_name, Variable var);
	std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByStmtNum(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByProcName(Procedure proc_name);
	std::shared_ptr<std::unordered_set<StmtNum>> GetUsesStmtNumByVar(Variable var);
	std::shared_ptr<std::unordered_set<Procedure>> GetUsesProcNameByVar(Variable var);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllUsesStatements();
	std::shared_ptr<std::unordered_set<Procedure>> GetAllUsesProcedures();
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVUses();
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVUses();

	// APIs related to Modifies relation
	bool CheckModifies(StmtNum stmt_num, Variable var);
	bool CheckModifies(Procedure proc_name, Variable var);
	std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByStmtNum(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByProcName(Procedure proc_name);
	std::shared_ptr<std::unordered_set<StmtNum>> GetModifiesStmtNumByVar(Variable var);
	std::shared_ptr<std::unordered_set<Procedure>> GetModifiesProcNameByVar(Variable var);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllModifiesStatements();
	std::shared_ptr<std::unordered_set<Procedure>> GetAllModifiesProcedures();
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies();
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies();

	// APIs related to Follows relation
	virtual bool CheckFollows(StmtNum left, StmtNum right);
	virtual bool IsFollowsStoreEmpty();
	virtual StmtNum GetSuccessorStmtFromStmt(StmtNum stmt);
	virtual StmtNum GetPredecessorStmtFromStmt(StmtNum stmt);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmts();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmts();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations();
};