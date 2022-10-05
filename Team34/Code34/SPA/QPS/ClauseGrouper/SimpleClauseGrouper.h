#pragma once

#include "ClauseGrouper.h"

/*
* This class will only create one clause group for each type of group. 
*/
class SimpleClauseGrouper 
	: public ClauseGrouper
{
	void Group();
};

