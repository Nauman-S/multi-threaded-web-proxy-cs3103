#pragma once

#include <memory>
#include "design_extractor/Extractable.h"
#include "design_extractor/NodeExtractor.h"

using namespace std;

class ASTNode: public Extractable {
public:
	void SetParent(shared_ptr<ASTNode>);

	shared_ptr<ASTNode> GetParent();

	virtual void Extract(NodeExtractor&) = 0;

protected:
	shared_ptr<ASTNode> parent;
};
