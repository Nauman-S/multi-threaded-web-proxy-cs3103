#pragma once

#include "NodeExtractor.h"

class Extractable {
public:
	virtual void Extract(NodeExtractor&) = 0;
};

