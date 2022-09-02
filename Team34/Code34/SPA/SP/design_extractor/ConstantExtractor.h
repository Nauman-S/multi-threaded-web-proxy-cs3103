#pragma once

#include "NodeExtractor.h"

class ConstantExtractor : public NodeExtractor {
public:
	virtual void ExtractProcedureNode();
	virtual void ExtractReadNode();
	virtual void ExtractCallNode();
};

