#pragma once
# include "ASTNode.h"
# include "LineIndex.h"
# include <string>
# include "VariableIndex.h"
# include <vector>
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

	// virtual vector<VariableIndex> getModifies() = 0;

protected:
	LineIndex lineIndex;
	StatementType statement_type;
	std::string type_val;
};
