#pragma once
#include <string>
#include <vector>

#include "QueryLexer.h"

#include "..\reference\Ref.h"
#include "..\reference\StmtRef.h"
#include "..\relation\Rel.h"
#include "..\reference\VarRef.h"
#include "../pattern/Pattern.h"
#include "../Query.h"


#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
class QueryBuilder
{
private:
	QueryLexer* lexer_;

	std::vector<Ref*> ParseDeclarationStatements();
	Query* ParseSelectStatement(std::vector<Ref*> synonyms_);

	Ref* ParseDeclarationStatement();
	Ref* CreateReference(std::string design_entity_, std::string synonym_);//This method should ideally be inside Ref Class based on factory method

	std::vector<Ref*> ParseReturnValues(std::vector<Ref*> synonyms_);
	bool HasSuchThatClause();
	std::vector<Rel*> ParseRelations(std::vector<Ref*> synonyms_);
	Rel* ParseRelRefClause(std::string relation_reference_, std::vector<Ref*> synonyms_);
	std::vector<Pattern*> ParsePatterns();

	VarRef* GetRhsVarRef(std::vector<Ref*> synonyms_);

public:

	QueryBuilder();
	std::optional<Query*> GetQuery(const std::string& query_string);
};

#endif



