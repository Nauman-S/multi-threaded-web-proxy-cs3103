#pragma once

#include "design_extractor/Extractable.h"
#include "design_extractor/NodeExtractor.h"

class ASTNode: public Extractable {
public:
	void setParent(ASTNode*);

	ASTNode* getParent();

	virtual void Extract(NodeExtractor&) = 0;

protected:
	ASTNode* parent;
};
