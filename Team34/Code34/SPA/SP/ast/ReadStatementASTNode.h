#pragma once

#include <string>
#include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

using namespace std;

class ReadStatementASTNode : public StatementASTNode {
public:
	void SetVariable(Variable&);
	virtual Variable GetReadVariable() const;

	virtual void Extract(NodeExtractor&) override;
	virtual string Stringify() override;

protected:
	Variable var;
};
