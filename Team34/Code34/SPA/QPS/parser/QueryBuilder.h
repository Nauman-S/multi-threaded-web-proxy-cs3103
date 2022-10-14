#pragma once
#include <string>
#include <vector>
#include <memory>

#include "QueryLexer.h"
#include "..\reference\Ref.h"
#include "..\reference\StmtRef.h"
#include "..\relation\Rel.h"
#include "..\reference\VarRef.h"
#include "..\pattern\Pattern.h"
#include "..\Query.h"
#include "../../Utils/algo/PostfixConverter.h"
#include "../AttrType.h"

using std::shared_ptr;
using std::vector;

class QueryBuilder
{
private:
	shared_ptr<QueryLexer> lexer_;
	vector<shared_ptr<Ref>> declared_synonyms_;
	PostfixConverter postfix_converter_;
	

	std::unordered_set<RefType> stmt_ref_types = std::unordered_set<RefType>({ RefType::kAssignRef, RefType::kCallRef, RefType::kIfRef, RefType::kPrintRef, RefType::kReadRef, RefType::kWhileRef });

	std::vector<shared_ptr<Ref>>  ParseDeclarationStatements();
	std::vector<shared_ptr<Ref>>  ParseDeclarationStatement();

	shared_ptr<Query> ParseSelectStatement();	
	std::shared_ptr<std::vector<shared_ptr<Ref>>> ParseReturnValues();


	shared_ptr<StmtRef> ParseStmtRef();
	shared_ptr<ProcRef> ParseProcRef();
	shared_ptr<VarRef> ParseVarRef();
	shared_ptr<ExprSpec> ParseExpression();

	string GetExpressionStr();

	std::vector<shared_ptr<Rel>> ParseRelations();
	shared_ptr<Rel> QueryBuilder::ParseRelation();
	shared_ptr<Rel> ParseRelRefClause(std::string relation_reference_);
	shared_ptr<Rel> ParseUsesRel();
	shared_ptr<Rel> ParseModifiesRel();
	shared_ptr<Rel> ParseFollowsRel();
	shared_ptr<Rel> ParseFollowsTRel();
	shared_ptr<Rel> ParseParentRel();
	shared_ptr<Rel> ParseParentTRel();
	shared_ptr<Rel> ParseNextRel();
	shared_ptr<Rel> ParseNextTRel();
	shared_ptr<Rel> ParseAffectsRel();
	shared_ptr<Rel> ParseAffectsTRel();
	shared_ptr<Rel> ParseCallsRel();
	shared_ptr<Rel> ParseCallsTRel();

	std::pair<shared_ptr<Ref>, shared_ptr<VarRef>> GetModifiesOrUsesSyns();
	std::pair<shared_ptr<StmtRef>, shared_ptr<StmtRef>> GetStmtStmtSyns();
	std::pair<shared_ptr<ProcRef>, shared_ptr<ProcRef>> GetProcProcSyns();

	std::vector< shared_ptr<Pattern>> ParsePatterns();
	shared_ptr<Pattern> ParsePattern();

	std::vector<shared_ptr<With>> ParseWithClauses();
	shared_ptr<With> ParseWithClause();
	std::pair<shared_ptr<Ref>, AttrType> ParseWithRef();

	AttrType ParseAttr(shared_ptr<Ref> syn);
	void ValidateAttrName(shared_ptr<Ref> synonym, string ref_name);
	AttrType GetAttrTypeFromName(string);

	shared_ptr<VarRef> GetRhsVarRef(std::vector<shared_ptr<Ref>> select_synonyms_);

	shared_ptr<Ref> GetDeclaredSyn(string name);
	shared_ptr<Ref> GetDeclaredSyn(string name, RefType attr_name);
	bool ContainsSynonym(string syn_name);
	

public:
	QueryBuilder();
	std::shared_ptr<Query> GetQuery(const std::string& query_string);
};



