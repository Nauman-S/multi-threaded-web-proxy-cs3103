#pragma once
#include "reference/Ref.h"
#include "relation/Rel.h"
#include "pattern/Pattern.h"

#include <vector>
class Query
{
protected:
	std::vector<Ref> select_tuple_;
	std::vector<Rel> relations_;
	std::vector<Pattern> patterns_;
};

