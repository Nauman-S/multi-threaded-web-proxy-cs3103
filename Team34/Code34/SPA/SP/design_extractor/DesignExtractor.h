#pragma once

#include <string>
#include <memory>

#include "../ast/ProgramNode.h"

class DesignExtractor {
public:
    void PopulatePKB(std::shared_ptr<ProgramNode>);
};

