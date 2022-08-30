#pragma once
#include "manager/ModifiesManager.h"
#include "manager/UsesManager.h"

class WritePKBManager
{
public:
	// APIs related to Uses relation
	void SetUses(int stmt_num, std::string var);
	void SetUses(std::string proc_name, std::string var);

	//APIs related to Modifies relation
	void SetModifies(int stmt_num, std::string var);
	void SetModifies(std::string proc_name, std::string var);
private:
	ModifiesManager modifies_manager_;
	UsesManager uses_manager_;
};