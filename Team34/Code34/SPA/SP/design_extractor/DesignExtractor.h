#pragma once

#include <string>

#include "../ProgramNode.h"

class DesignExtractor {
public:
	void PopulatePKB(ProgramNode&);

	// TODO: Combine into populate PKB when parser supports constants
	void AddConstants(const std::string&);
};

