#pragma once

#include <memory>

#include "SetRes.h"
#include "TableRes.h"
#include "ResType.h"


class ResWrapper
{
protected:
	std::shared_ptr<SetRes> set_res_;
	std::shared_ptr<TableRes> table_res_;
	bool is_valid_;
	ResType type_;

public:
	ResWrapper(std::shared_ptr<SetRes> set)
		: set_res_{ set }, table_res_{ nullptr }, is_valid_{ true }, type_{ ResType::kSet } {};

	ResWrapper(std::shared_ptr<TableRes> table)
		: set_res_{ nullptr }, table_res_{ table }, is_valid_{ true }, type_{ ResType::kTable } {};

	ResWrapper(bool valid) 
		: set_res_{ nullptr }, table_res_{ nullptr }, is_valid_{ valid }, type_{ ResType::kBool } {};

	ResType GetResType() { return type_; }

	bool IsValid() { return is_valid_; }

	std::shared_ptr<SetRes> GetSet() { return set_res_; }

	std::shared_ptr<TableRes> GetTable() { return table_res_; }
};

