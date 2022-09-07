#pragma once
#include <string>
#include <vector>

#include "QueryLexer.h"

#include "..\reference\Ref.h"
#include "..\reference\StmtRef.h"
#include "..\relation\Rel.h"
#include "..\reference\VarRef.h"
#include "..\pattern\Pattern.h"
#include "..\Query.h"
#include "..\reference\RefFactory.h"



#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <memory>

using std::shared_ptr;
using std::vector;

class QueryBuilder
{
private:
	shared_ptr<QueryLexer> lexer_;
	vector<shared_ptr<Ref>> synonyms_;
	std::vector<shared_ptr<Rel>> relations_;

	std::unordered_set<RefType> stmt_ref_types = std::unordered_set<RefType>({ RefType::kAssignRef, RefType::kCallRef, RefType::kIfRef, RefType::kPrintRef, RefType::kReadRef, RefType::kWhileRef });



	std::vector<shared_ptr<Ref>> ParseDeclarationStatements();
	shared_ptr<Query> ParseSelectStatement();

	shared_ptr<Ref> ParseDeclarationStatement(RefFactory* ref_factory_);

	std::vector<shared_ptr<Ref>> ParseReturnValues();
	//shared_ptr<Ref> ParseNextRef();

	bool HasSuchThatClause();

	shared_ptr<Ref> GetNextStmtRef();
	shared_ptr<Ref> GetNextProcRef();
	shared_ptr<Ref> GetNextVarRef();
	//shared_ptr<Ref> GetNextConstRef();


	std::vector< shared_ptr<Rel>> ParseRelations();
	shared_ptr<Rel> ParseRelRefClause(std::string relation_reference_);
	shared_ptr<Rel> ParseUsesRel();
	shared_ptr<Rel> ParseModifiesRel();
	

	std::vector< shared_ptr<Pattern>> ParsePatterns();

	shared_ptr<VarRef> GetRhsVarRef(std::vector<shared_ptr<Ref>> synonyms_);

	shared_ptr<Ref> GetDeclaredSyn(string name);
	shared_ptr<Ref> GetDeclaredSyn(string name, RefType ref_type);

public:

	QueryBuilder();
	std::shared_ptr<Query> GetQuery(const std::string& query_string);
};

#endif



