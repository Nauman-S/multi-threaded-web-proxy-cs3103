#pragma once
# include "ASTNode.h"
# include "LineIndex.h"
# include <string>

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

protected:
	LineIndex lineIndex;
	StatementType statement_type;
	std::string type_val;
};
