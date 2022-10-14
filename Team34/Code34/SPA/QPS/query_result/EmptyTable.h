#pragma once

#include "Table.h"

class EmptyTable
	: public Table 
{
public:
	EmptyTable::EmptyTable() {
		is_empty_ = true;
	}
};