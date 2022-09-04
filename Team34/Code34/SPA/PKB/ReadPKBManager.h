#pragma once
#include <vector>
#include <unordered_set>
#include <memory>

#include "manager/VariableManager.h"
#include "manager/ConstantManager.h"
#include "manager/ProcedureManager.h"
#include "manager/EntityManager.h"
#include "manager/StatementManager.h"
#include "manager/ModifiesManager.h"
#include "manager/UsesManager.h"
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
	std::shared_ptr<std::unordered_set<Procedure>> GetAllProcedures();

	// APIs related to Statements
	bool IsStatement(StmtNum stmt_num);
	RefType GetStatementType(StmtNum stmt_num);
	std::shared_ptr<std::unordered_set<StmtNum>> GetStatementsByType(RefType type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllStatements();

	// APIs related to Uses relation
	bool CheckUses(int stmt_num, std::string var);
	bool CheckUses(std::string proc_name, std::string var);
	const std::vector<std::pair<int, std::string>>& GetAllSVUses();
	const std::vector<std::pair<std::string, std::string>>& GetAllPVUses();
	std::unordered_set<std::string> GetUsesVarByStmtNum(int stmt_num);
	std::unordered_set<std::string> GetUsesVarByProcName(std::string proc_name);
	std::unordered_set<int> GetUsesStmtNumByVar(std::string var);
	std::unordered_set<std::string> GetUsesProcNameByVar(std::string var);
	
	// APIs related to Modifies relation
	bool CheckModifies(int stmt_num, std::string var);
	bool CheckModifies(std::string proc_name, std::string var);
	const std::vector<std::pair<int, std::string>>& GetAllSVModifies();
	const std::vector<std::pair<std::string, std::string>>& GetAllPVModifies();
	std::unordered_set<std::string> GetModifiesVarByStmtNum(int stmt_num);
	std::unordered_set<std::string> GetModifiesVarByProcName(std::string proc_name);
	std::unordered_set<int> GetModifiesStmtNumByVar(std::string var);
	std::unordered_set<std::string> GetModifiesProcNameByVar(std::string var);
private:
    VariableManager variable_manager_;
    ConstantManager constant_manager_;
	ProcedureManager procedure_manager_;
	StatementManager statement_manager_;
	ModifiesManager modifies_manager_;
	UsesManager uses_manager_;
};