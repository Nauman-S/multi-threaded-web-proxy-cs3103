#pragma once

#include <memory>
#include "../design_extractor/Extractable.h"
#include "../design_extractor/NodeExtractor.h"

using namespace std;

class ASTNode: public Extractable {
public:
	virtual void Extract(NodeExtractor&) = 0;
};
