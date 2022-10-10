#pragma once

#include <memory>
#include <vector>
#include <string>

#include "ASTNode.h"
#include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class ProcedureASTNode : public ASTNode {
public:
	Procedure GetProc() const;
	std::vector<std::shared_ptr<StatementASTNode>> GetChildren() const;

	void SetProc(Procedure&);
	void SetChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	virtual void Extract(NodeExtractor&) override;
	virtual string Stringify() override;

protected:
	Procedure proc;
	std::vector<std::shared_ptr<StatementASTNode>> children;
};
