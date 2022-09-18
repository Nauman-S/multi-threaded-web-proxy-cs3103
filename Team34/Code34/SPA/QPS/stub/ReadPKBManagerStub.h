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

		And the PQL decalration:
		Procedure p1, p2; Variable v1, v2; Assign s1; 
	
	*/
	// APIs related to Statements
	RefType GetStatementType(StmtNum stmt_num);

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
};