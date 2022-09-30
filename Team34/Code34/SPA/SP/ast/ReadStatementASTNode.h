#pragma once

#include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class ReadStatementASTNode : public StatementASTNode {
public:
	void SetVariable(Variable&);

	virtual Variable GetReadVariable();

	virtual void Extract(NodeExtractor&) override;


protected:
	Variable var;
};
