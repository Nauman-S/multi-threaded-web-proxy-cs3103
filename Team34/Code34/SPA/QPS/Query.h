#pragma once
#include "reference/Ref.h"
#include "relation/Rel.h"
#include "pattern/Pattern.h"
#include "Clause.h"
#include "DataRetriever.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

class Query
{
protected:
	std::shared_ptr<std::vector<Ref>> select_tuple_;
	std::shared_ptr<std::vector<Rel>> relations_;
	std::shared_ptr < std::vector<Pattern>> patterns_;

public:
	Query() {};

	explicit Query(std::shared_ptr<std::vector<Ref>> select_tuple)
		: select_tuple_{ select_tuple_ } {};
	

	Query(std::shared_ptr<std::vector<Ref>> select_tuple, std::shared_ptr<std::vector<Rel>> relations)
		: select_tuple_{ select_tuple }, relations_{ relations } {};

	Query(std::shared_ptr<std::vector<Ref>> select_tuple, std::shared_ptr < std::vector<Pattern>> patterns)
		: select_tuple_{ select_tuple }, patterns_{patterns} {};

	Query(std::shared_ptr<std::vector<Ref>> select_tuple, std::shared_ptr<std::vector<Rel>> relations, std::shared_ptr < std::vector<Pattern>> patterns)
		: select_tuple_{ select_tuple }, relations_{ relations }, patterns_{ patterns } {};

	std::shared_ptr<std::vector<Rel>> GetRelations();
};

