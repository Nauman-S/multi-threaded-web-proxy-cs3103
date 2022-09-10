#pragma once
#include <vector>
#include <unordered_set>
#include <memory>

#include "PKB.h"
#include "../Utils/type/TypeDef.h"

class ReadPKBManager
{
public:
	static std::unique_ptr<ReadPKBManager> GetInstance()
	{
		std::unique_ptr<ReadPKBManager> manager(new ReadPKBManager());
		return manager;
	}
    // APIs related to Variable entity
    bool IsVariable(Variable var);
    const std::shared_ptr<std::unordered_set<Variable>> GetAllVariables();

    // APIs related to Constant entity
    bool IsConstant(Constant constant);
    const std::shared_ptr<std::unordered_set<Constant>> GetAllConstants();

	// APIs related to Procedure entity
	bool IsProcedure(Procedure proc);
	const std::shared_ptr<std::unordered_set<Procedure>> GetAllProcedures();

	// APIs related to Statements
	bool IsStatement(StmtNum stmt_num);
	RefType GetStatementType(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<StmtNum>> GetStatementsByType(RefType type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();

	// APIs related to Parent relation
	bool CheckParent(StmtNum child, StmtNum parent);
	std::shared_ptr<std::unordered_set<StmtNum>> GetChild(StmtNum parent);
	StmtNum GetParent(StmtNum child);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations();

	// APIs related to Parent* relation
	bool CheckParentS(StmtNum child, StmtNum parent);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentSRelations();

	// APIs related to Follows relation
	bool CheckFollows(StmtNum left, StmtNum right);
	StmtNum GetSuccessorStmt(StmtNum stmt);
	StmtNum GetPredecessorStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations();

	// APIs relation to Follows* relation
	bool CheckFollowsT(StmtNum left, StmtNum right);
	std::shared_ptr<std::vector<StmtNum>> GetAllSuccessorStmt(StmtNum stmt);
	std::shared_ptr<std::vector<StmtNum>> GetAllPredecessorStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsTRelations();

	// APIs related to Uses relation
	bool CheckUses(StmtNum stmt_num, Variable var);
	bool CheckUses(Procedure proc_name, Variable var);
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVUses();
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVUses();
	std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByStmtNum(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByProcName(Procedure proc_name);
	std::shared_ptr<std::unordered_set<StmtNum>> GetUsesStmtNumByVar(Variable var);
	std::shared_ptr<std::unordered_set<Procedure>> GetUsesProcNameByVar(Variable var);
	
	// APIs related to Modifies relation
	bool CheckModifies(StmtNum stmt_num, Variable var);
	bool CheckModifies(Procedure proc_name, Variable var);
	std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies();
	std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies();
	std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByStmtNum(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByProcName(Procedure proc_name);
	std::shared_ptr<std::unordered_set<StmtNum>> GetModifiesStmtNumByVar(Variable var);
	std::shared_ptr<std::unordered_set<Procedure>> GetModifiesProcNameByVar(Variable var);
};