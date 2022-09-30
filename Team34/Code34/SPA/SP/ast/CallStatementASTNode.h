#pragma once

# include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class CallStatementASTNode : public StatementASTNode {
public:
	void SetProcedure(Procedure& p);

	Procedure GetProcedure();

	virtual void Extract(NodeExtractor&) override;


protected:
	Procedure proc;
};
