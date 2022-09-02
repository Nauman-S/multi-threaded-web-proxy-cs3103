#pragma once
#include <memory>

#include "manager/VariableManager.h"
#include "manager/ConstantManager.h"
#include "manager/ModifiesManager.h"
#include "manager/UsesManager.h"

class WritePKBManager
{
public:
	static std::unique_ptr<WritePKBManager> GetInstance()
	{
		std::unique_ptr<WritePKBManager> manager(new WritePKBManager());
		return manager;
	}
    // APIs related to Variable entity
    void AddVariable(std::string var);

    // APIs related to Constant entity
    void AddConstant(int constant);

	// APIs related to Uses relation
	void SetUses(int stmt_num, std::string var);
	void SetUses(std::string proc_name, std::string var);

	//APIs related to Modifies relation
	void SetModifies(int stmt_num, std::string var);
	void SetModifies(std::string proc_name, std::string var);
private:
    VariableManager variable_manager_;
    ConstantManager constant_manager_;
	ModifiesManager modifies_manager_;
	UsesManager uses_manager_;
};