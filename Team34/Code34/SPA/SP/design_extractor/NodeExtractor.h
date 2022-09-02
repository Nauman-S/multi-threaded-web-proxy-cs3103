#pragma once

class NodeExtractor {
public:
	virtual void ExtractProcedureNode() = 0;
	virtual void ExtractReadNode() = 0;
	virtual void ExtractCallNode() = 0;
};

