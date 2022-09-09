#pragma once

#include <string>
#include <memory>

#include "../ProgramNode.h"

class DesignExtractor {
public:
	void PopulatePKB(std::shared_ptr<ProgramNode>);

	// TODO: Combine into populate PKB when parser supports constants
	void AddConstants(const std::string&);
};

