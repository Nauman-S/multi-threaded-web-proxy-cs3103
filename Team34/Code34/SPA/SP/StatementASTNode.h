#pragma once

#include <string>
#include <vector>

#include "ASTNode.h"
#include "LineIndex.h"
#include "VariableIndex.h"

enum class StatementType {
	sassign,
	sif,
	swhile,
	sexpre,
	sprint,
	sread,
	scall,
};

class StatementASTNode : public ASTNode {
public:
	LineIndex getLineIndex();

	void setLineIndex(LineIndex&);

	StatementType getStatementType();

	std::string getTypeVal();

	void setStatementType(StatementType, std::string);

	bool operator < (const StatementASTNode& c) const
	{
		return lineIndex < c.lineIndex;
	}

	virtual void Extract(NodeExtractor&) = 0;
	// virtual vector<VariableIndex> getModifies() = 0;

protected:
	LineIndex lineIndex;
	StatementType statement_type;
	std::string type_val;
};
