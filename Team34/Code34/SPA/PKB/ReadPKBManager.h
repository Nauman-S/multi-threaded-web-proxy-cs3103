#pragma once
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
	std::shared_ptr<RefType> GetStatementType(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<StmtNum>> GetStatementsByType(RefType type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();

	// APIs related to Parent relation
	virtual bool CheckParent(StmtNum parent, StmtNum child);
	virtual bool IsParentStoreEmpty();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetChildrenFromStmt(StmtNum parent);
	virtual StmtNum GetParentFromStmt(StmtNum child);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations();

	// APIs related to Parent* relation
	virtual bool CheckParentT(StmtNum parent, StmtNum child);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildrenFromStmt(StmtNum stmt);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllParentsFromStmt(StmtNum stmt);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentTRelations();

	// APIs related to Follows relation
	virtual bool CheckFollows(StmtNum left, StmtNum right);
	virtual bool IsFollowsStoreEmpty();
	virtual StmtNum GetSuccessorStmtFromStmt(StmtNum stmt);
	virtual StmtNum GetPredecessorStmtFromStmt(StmtNum stmt);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmts();
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmts();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations();


	// APIs relation to Follows* relation
	virtual bool CheckFollowsT(StmtNum left, StmtNum right);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmtsFromStmt(StmtNum stmt);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmtsFromStmt(StmtNum stmt);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsTRelations();

	// APIs related to Uses relation
	virtual bool CheckUses(StmtNum stmt_num, Variable var);
	virtual bool CheckUses(Procedure proc_name, Variable var);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByStmtNum(StmtNum stmt_num);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByProcName(Procedure proc_name);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetUsesStmtNumByVar(Variable var);
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetUsesProcNameByVar(Variable var);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllUsesStatements();
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetAllUsesProcedures();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVUses();
	virtual std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVUses();
	
	// APIs related to Modifies relation
	virtual bool CheckModifies(StmtNum stmt_num, Variable var);
	virtual bool CheckModifies(Procedure proc_name, Variable var);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByStmtNum(StmtNum stmt_num);
	virtual std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByProcName(Procedure proc_name);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetModifiesStmtNumByVar(Variable var);
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetModifiesProcNameByVar(Variable var);
	virtual std::shared_ptr<std::unordered_set<StmtNum>> GetAllModifiesStatements();
	virtual std::shared_ptr<std::unordered_set<Procedure>> GetAllModifiesProcedures();
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies();
	virtual std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies();

	// APIs related to Pattern relation
	virtual bool IsAssignPatternMatch(StmtNum stmt_num, std::shared_ptr<ExprSpec> expr);
	virtual bool IsAssignPatternMatch(StmtNum stmt_num, Variable var, std::shared_ptr<ExprSpec> expr);
	virtual std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAssignPatternMatch(std::shared_ptr<ExprSpec> expr);
};