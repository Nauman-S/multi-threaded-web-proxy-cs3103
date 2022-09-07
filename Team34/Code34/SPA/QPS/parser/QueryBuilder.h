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


	std::vector<shared_ptr<Ref>> ParseDeclarationStatements();
	shared_ptr<Query> ParseSelectStatement();

	shared_ptr<Ref> ParseDeclarationStatement();
	shared_ptr<Ref> CreateReference(std::string design_entity_, std::string synonym_);//This method should ideally be inside Ref Class based on factory method

	std::vector<shared_ptr<Ref>> ParseReturnValues();
	bool HasSuchThatClause();
	std::vector< shared_ptr<Rel>> ParseRelations();
	shared_ptr<Rel> ParseRelRefClause(std::string relation_reference_);
	shared_ptr<Rel> ParseUseRef(std::vector<shared_ptr<Ref>> synonyms_);

	std::vector< shared_ptr<Pattern>> ParsePatterns();

	shared_ptr<VarRef> GetRhsVarRef(std::vector<shared_ptr<Ref>> synonyms_);

public:

	QueryBuilder();
	std::shared_ptr<Query> GetQuery(const std::string& query_string);
};

#endif



