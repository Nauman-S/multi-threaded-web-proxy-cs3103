#include "QueryBuilder.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <unordered_set>

#include "SyntaxError.h"
#include "SemanticError.h"
#include "..\..\Utils\InvalidTokenException.h"
#include "..\..\Utils\expression\ExprSpec.h"
#include "..\..\Utils\expression\PartialExprSpec.h"
#include "..\..\Utils\expression\WildcardExprSpec.h"
#include "..\..\Utils\expression\ExactExprSpec.h"
#include "..\reference\ValType.h"
#include "..\reference\Ref.h"
#include "..\reference\EntityRef.h"
#include "..\reference\TempRef.h"
#include "..\relation\Rel.h"
#include "..\relation\FollowsRel.h"
#include "..\relation\FollowsTRel.h"
#include "..\relation\ParentRel.h"
#include "..\relation\ParentTRel.h"
#include "..\relation\UsesSRel.h"
#include "..\relation\UsesPRel.h"
#include "..\relation\NextRel.h"
#include "..\relation\NextTRel.h"
#include "..\relation\AffectsRel.h"
#include "..\relation\AffectsTRel.h"
#include "..\relation\CallsRel.h"
#include "..\relation\CallsTRel.h"
#include "../pattern/Pattern.h"
#include "../pattern/AssignPattern.h"
#include "../pattern/IfPattern.h"
#include "../pattern/WhilePattern.h"
#include "../with_clause/With.h"

using std::shared_ptr;
using std::vector;

QueryBuilder::QueryBuilder() {
	lexer_ = std::make_shared<QueryLexer>();
}

shared_ptr<Query> QueryBuilder::GetQuery(const std::string& query_string_) {
		this->lexer_->FeedQuery(query_string_);
		
		synonyms_ = ParseDeclarationStatements();
		
		shared_ptr<Query> query_ = ParseSelectStatement();
		//std::shared_ptr<Query> sp_ = std::shared_ptr<Query>(query_);
		return query_;
}

std::vector<shared_ptr<Ref>> QueryBuilder::ParseDeclarationStatements() {
	std::vector<shared_ptr<Ref>> synonyms;
	std::vector<shared_ptr<Ref>> curr_synonyms;

	std::unordered_set<string> used_names;


	while (this->lexer_->HasDesignEntity()) {
		curr_synonyms = ParseDeclarationStatement();
		for (auto syn : curr_synonyms) {
			if (!used_names.count(syn->GetName())) {
				used_names.insert(syn->GetName());
				synonyms.push_back(syn);
			}
			else {
				throw SemanticError("The synonym " + syn->GetName() + " is already declared");
			}
		}
	}

	return synonyms;
}



std::vector<shared_ptr<Ref>> QueryBuilder::ParseDeclarationStatement() {
	std::string design_entity_ = this->lexer_->MatchDesignEntityKeyword();

	std::vector<shared_ptr<Ref>> curr_synonyms;

	if (lexer_->HasIdentity()) {
		std::string synonym_ = lexer_->MatchIdentity();
		curr_synonyms.push_back(EntityRef::CreateReference(design_entity_, synonym_));

		while (lexer_->HasComma()) {
			lexer_->MatchComma();
			std::string synonym_ = lexer_->MatchIdentity();
			curr_synonyms.push_back(EntityRef::CreateReference(design_entity_, synonym_));
		}

		if (this->lexer_->HasEndOfDeclarationStatement()) {
			this->lexer_->MatchEndOfDeclarationStatement();
		}
		else {
			throw SyntaxError("Declaration Statement - Missing semicolon (;) at end of statement");
		}
		return curr_synonyms;

	}
	else {
		throw SyntaxError("Declaration Statement - Missing Synonym");
	}

}

shared_ptr<Query> QueryBuilder::ParseSelectStatement() {
	lexer_->MatchKeyword("Select");
	shared_ptr<vector<shared_ptr<Ref>>> select_tuple = ParseReturnValues();

	shared_ptr<vector<shared_ptr<Rel>>> relations = std::make_shared<vector<shared_ptr<Rel>>>();
	shared_ptr<vector<shared_ptr<Pattern>>> patterns = std::make_shared<vector<shared_ptr<Pattern>>>();
	shared_ptr<vector<shared_ptr<With>>> with_clauses = std::make_shared<vector<shared_ptr<With>>>();
	while (lexer_->HasPatternKeyword() || lexer_->HasSuchThatKeywords() || lexer_->HasWithKeyword()) {
			
		if (lexer_->HasPatternKeyword()) {
			vector<shared_ptr<Pattern>> curr_patterns = ParsePatterns();
			patterns->insert(patterns->end(), curr_patterns.begin(), curr_patterns.end());

		}
		else if (lexer_->HasSuchThatKeywords()) {
			vector<shared_ptr<Rel>> curr_relations = ParseRelations();
			// append new relations to the end of all relations
			relations->insert(relations->end(), curr_relations.begin(), curr_relations.end());
		}
		else if (lexer_->HasWithKeyword()) {
			vector<shared_ptr<With>> curr_with_clauses = ParseWithClauses();
			with_clauses->insert(with_clauses->end(), curr_with_clauses.begin(), curr_with_clauses.end());
		}
	}

	if (this->lexer_->HasMoreTokens()) {
		throw SyntaxError("Unexpected token at end of query");
	}


	//std::shared_ptr <std::vector<std::shared_ptr<Rel>>> relations_s_ = std::make_shared<std::vector<std::shared_ptr<Rel>>>();
	//for (shared_ptr<Rel> rel_ : relations) {
	//	std::shared_ptr <Rel> rel_s_ = std::shared_ptr<Rel>(rel_);
	//	relations_s_->push_back(rel_s_);
	//}

	//std::shared_ptr < std::vector<std::shared_ptr<Pattern>>> patterns_s_ = std::make_shared<std::vector<std::shared_ptr<Pattern>>>();
	//for (shared_ptr<Pattern> pattern_ : patterns) {
	//	std::shared_ptr <Pattern> pattern_s_ = std::shared_ptr<Pattern>(pattern_);
	//	patterns_s_->push_back(pattern_s_);
	//}

	shared_ptr<Query> query;
	if (select_tuple->size() == 0) {
		query = shared_ptr<Query>(new Query(relations, patterns, with_clauses));
	}
	else {
		query = shared_ptr<Query>(new Query(select_tuple, relations, patterns, with_clauses));
	}
	return query;

}

shared_ptr<vector<shared_ptr<Ref>>> QueryBuilder::ParseReturnValues() {
	shared_ptr<vector<shared_ptr<Ref>>> select_tuple = shared_ptr<vector<shared_ptr<Ref>>>(new vector<shared_ptr<Ref>>());
	std::string syn_name;
	if (lexer_->HasBooleanKeyword()) {
		lexer_->MatchBooleanKeyword();
		return select_tuple;
	}
	else if (lexer_->HasIdentity()) {
		syn_name = lexer_->MatchIdentity();
		select_tuple->push_back(GetDeclaredSyn(syn_name));
	}
	else if (lexer_->HasLeftAngle()) {
		lexer_->MatchLeftAngle();
		syn_name = lexer_->MatchIdentity();
		select_tuple->push_back(GetDeclaredSyn(syn_name));

		while (lexer_->HasComma()) {
			lexer_->MatchComma();
			syn_name = lexer_->MatchIdentity();
			select_tuple->push_back(GetDeclaredSyn(syn_name));
		}
		lexer_->MatchRightAngle();
	}
	else {
		throw SyntaxError("Select Statement - Missing synonyms to be returned");
	}
	return select_tuple;
}


std::vector<shared_ptr<Rel>> QueryBuilder::ParseRelations() {
	std::vector<shared_ptr<Rel>> relations;
	lexer_->MatchSuchThatKeywords();

	relations.push_back(ParseRelation());

	while (lexer_->HasAndKeyword()) {
		lexer_->MatchAndKeyword();
		relations.push_back(ParseRelation());
	}

	return relations;
}

shared_ptr<Rel> QueryBuilder::ParseRelation() {
	std::string relation_name;

	relation_name = lexer_->MatchReferenceKeyword();

	lexer_->MatchLeftBrace();

	shared_ptr<Rel> relation = ParseRelRefClause(relation_name);

	lexer_->MatchRightBrace();

	return relation;
}

shared_ptr<Rel> QueryBuilder::ParseRelRefClause(std::string relation_name) {
	if (relation_name == "Follows") {
		return ParseFollowsRel();
	} 
	else if (relation_name == "Follows*") {
		return ParseFollowsTRel();
	}
	else if (relation_name == "Parent") {
		return ParseParentRel();
	}
	else if (relation_name == "Parent*") {
		return ParseParentTRel();
	}
	else if (relation_name == "Uses") {
		return ParseUsesRel();
	}
	else if (relation_name == "Modifies") {
		return ParseModifiesRel();
	}
	else if (relation_name == "Next") {
		return ParseNextRel();
	}
	else if (relation_name == "Next*") {
		return ParseNextTRel();
	}
	else if (relation_name == "Affects") {
		return ParseAffectsRel();
	} 
	else if (relation_name == "Affects*") {
		return ParseAffectsTRel();
	}
	else if (relation_name == "Calls") {
		return ParseCallsRel();
	}
	else if (relation_name == "Calls*") {
		return ParseCallsTRel();
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - unidentifiable relRef: " + relation_name);
	}
}

shared_ptr<Rel> QueryBuilder::ParseUsesRel() {
	auto [lhs_syn, rhs_syn] = GetModifiesOrUsesSyns();

	if (lhs_syn->GetRefType() == RefType::kProcRef) {
		return shared_ptr<Rel>(new UsesPRel(std::dynamic_pointer_cast<ProcRef>(lhs_syn), rhs_syn));
	}
	else {
		return shared_ptr<Rel>(new UsesSRel(std::dynamic_pointer_cast<StmtRef>(lhs_syn), rhs_syn));
	}
}

shared_ptr<Rel> QueryBuilder::ParseModifiesRel() {
	auto [lhs_syn, rhs_syn] = GetModifiesOrUsesSyns();

	if (lhs_syn->GetRefType() == RefType::kProcRef) {
		return shared_ptr<Rel>(new ModifiesPRel(std::dynamic_pointer_cast<ProcRef>(lhs_syn), rhs_syn));
	}
	else {
		return shared_ptr<Rel>(new ModifiesSRel(std::dynamic_pointer_cast<StmtRef>(lhs_syn), rhs_syn));
	}
}

shared_ptr<Rel> QueryBuilder::ParseFollowsRel() {
	auto [lhs_syn, rhs_syn] = GetStmtStmtSyns();
	return shared_ptr<Rel>(new FollowsRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseFollowsTRel() {
	auto [lhs_syn, rhs_syn] = GetStmtStmtSyns();
	return shared_ptr<Rel>(new FollowsTRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseParentRel() {
	auto [lhs_syn, rhs_syn] = GetStmtStmtSyns();
	return shared_ptr<Rel>(new ParentRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseParentTRel() {
	auto [lhs_syn, rhs_syn] = GetStmtStmtSyns();
	return shared_ptr<Rel>(new ParentTRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseNextRel() {
	auto [lhs_syn, rhs_syn] = GetStmtStmtSyns();
	return shared_ptr<Rel>(new NextRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseNextTRel() {
	auto [lhs_syn, rhs_syn] = GetStmtStmtSyns();
	return shared_ptr<Rel>(new NextTRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseAffectsRel() {
	auto [lhs_syn, rhs_syn] = GetStmtStmtSyns();
	return shared_ptr<Rel>(new AffectsRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseAffectsTRel() {
	auto [lhs_syn, rhs_syn] = GetStmtStmtSyns();
	return shared_ptr<Rel>(new AffectsTRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseCallsRel() {
	auto [lhs_syn, rhs_syn] = GetProcProcSyns();
	return shared_ptr<Rel>(new CallsRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseCallsTRel() {
	auto [lhs_syn, rhs_syn] = GetProcProcSyns();
	return shared_ptr<Rel>(new CallsTRel(lhs_syn, rhs_syn));
}

std::pair<shared_ptr<Ref>, shared_ptr<VarRef>> QueryBuilder::GetModifiesOrUsesSyns() {
	shared_ptr<Ref> lhs_syn;
	shared_ptr<VarRef> rhs_syn;
	
	if (lexer_->HasUnderScore()) {
		throw SemanticError("The first EntRef in Modifies and Uses relation cannot be WildCard");
	}

	if (lexer_->HasIdentity()) {
		string ref_name = lexer_->MatchIdentity();
		lhs_syn = GetDeclaredSyn(ref_name);
		if (lhs_syn->GetRefType() != RefType::kProcRef && lhs_syn->GetRefType() != RefType::kStmtRef
			&& !stmt_ref_types.count(lhs_syn->GetRefType())) {
			throw SemanticError("Type of synonym " + lhs_syn->GetName() + " is unmatched to declared type");
		}

	} 
	else if (lexer_->HasInteger()) {
		lhs_syn = ParseStmtRef();
	}
	else {
		lhs_syn = ParseProcRef();
	}

	lexer_->MatchComma();

	rhs_syn = ParseVarRef();
	return { lhs_syn, rhs_syn };
}

std::pair<shared_ptr<StmtRef>, shared_ptr<StmtRef>> QueryBuilder::GetStmtStmtSyns() {
	shared_ptr<StmtRef> lhs_syn = ParseStmtRef();
	lexer_->MatchComma();
	shared_ptr<StmtRef> rhs_syn = ParseStmtRef();
	return { lhs_syn, rhs_syn };
}

std::pair<shared_ptr<ProcRef>, shared_ptr<ProcRef>> QueryBuilder::GetProcProcSyns() {
	shared_ptr<ProcRef> lhs_syn = ParseProcRef();
	lexer_->MatchComma();
	shared_ptr<ProcRef> rhs_syn = ParseProcRef();
	return { lhs_syn, rhs_syn };
}


shared_ptr<StmtRef> QueryBuilder::ParseStmtRef() {
	shared_ptr<StmtRef> stmt_ref;
	if (lexer_->HasInteger()) {
		int line_number = lexer_->MatchInteger();
		stmt_ref = std::make_shared<StmtRef>(ValType::kLineNum, std::to_string(line_number));
	}
	else if (lexer_->HasUnderScore()) {
		lexer_->MatchUnderScore();
		stmt_ref = std::make_shared<StmtRef>(ValType::kWildcard, "");
	}
	else if (lexer_->HasIdentity()) {
		string ref_name = lexer_->MatchIdentity();
		stmt_ref = std::dynamic_pointer_cast<StmtRef>(GetDeclaredSyn(ref_name, RefType::kStmtRef));
	}
	else {
		throw SyntaxError("Incorrect Reference Type: Not a stmt type");
	}
	return stmt_ref;
};

shared_ptr<ProcRef> QueryBuilder::ParseProcRef() {
	shared_ptr<ProcRef> proc_ref;
	if (lexer_->HasQuotationMarks()) {
		lexer_->MatchQuotationMarks();
		string proc_name = lexer_->MatchIdentity();
		lexer_->MatchQuotationMarks();
		proc_ref = std::make_shared<ProcRef>(ValType::kProcName, proc_name);
	}
	else if (lexer_->HasUnderScore()) {
		lexer_->MatchUnderScore();
		proc_ref = std::make_shared<ProcRef>(ValType::kWildcard, "");
	}
	else if (lexer_->HasIdentity()) {
		string proc_name = lexer_->MatchIdentity();
		proc_ref = std::dynamic_pointer_cast<ProcRef>(GetDeclaredSyn(proc_name, RefType::kProcRef));
	}
	else {
		throw SyntaxError("Incorrect Reference Type: Not a Proc type");
	}
	return proc_ref;
}

shared_ptr<VarRef> QueryBuilder::ParseVarRef() {
	shared_ptr<VarRef> var_ref;
	if (lexer_->HasQuotationMarks()) {
		lexer_->MatchQuotationMarks();
		string var_name = lexer_->MatchIdentity();
		lexer_->MatchQuotationMarks();
		var_ref = std::make_shared<VarRef>(ValType::kVarName, var_name);
	}
	else if (lexer_->HasUnderScore()) {
		lexer_->MatchUnderScore();
		var_ref = std::make_shared<VarRef>(ValType::kWildcard, "");
	}
	else if (lexer_->HasIdentity()) {
		string var_name = lexer_->MatchIdentity();
		var_ref = std::dynamic_pointer_cast<VarRef>(GetDeclaredSyn(var_name, RefType::kVarRef));
	}
	else {
		throw SyntaxError("Incorrect Reference Type: Not a Var type");
	}
	return var_ref;
}


shared_ptr<Ref> QueryBuilder::GetDeclaredSyn(string name) {
	for (shared_ptr<Ref> synonym : synonyms_) {
		if (synonym->GetName() == name) {
			return synonym;
		}
	}
	throw SemanticError("Synonym " + name + " is not declared before use.");
}

shared_ptr<Ref> QueryBuilder::GetDeclaredSyn(string name, RefType ref_type) {
	for (shared_ptr<Ref> synonym : synonyms_) {
		if (synonym->GetName() == name) {
			if (synonym->GetRefType() == ref_type) {
				return synonym;
			}
			else if (ref_type == RefType::kStmtRef && stmt_ref_types.count(synonym->GetRefType())) {
				return synonym;
			}
			else {
				throw SemanticError("Type of synonym " + name + " is unmatched to declared type");
			}
			 
		}
	}
	throw SemanticError("Synonym " + name + " is not declared before use.");
}


shared_ptr<VarRef> QueryBuilder::GetRhsVarRef(std::vector<shared_ptr<Ref>> synonyms_) {
	if (this->lexer_->HasComma()) {
		this->lexer_->MatchComma();
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - missing comma (,) between LHS and RHS of relRef");
	}

	if (this->lexer_->HasIdentity()) {
		std::string identity_rhs_ = this->lexer_->MatchIdentity();
		for (shared_ptr<Ref> synonym_var_rhs_ : synonyms_) {

			if (synonym_var_rhs_->GetValType() == ValType::kSynonym && synonym_var_rhs_->GetRefType() == RefType::kVarRef && synonym_var_rhs_->GetName().compare(identity_rhs_) == 0) {
				shared_ptr <VarRef> rhs_ = std::dynamic_pointer_cast<VarRef>(synonym_var_rhs_);
				return rhs_;
			}
		}
		throw SyntaxError("Select statement - [suchthatcl] - no valid var synonym found on rhs of relRef");
	}
	else if (this->lexer_->HasQuotationMarks()) {
		this->lexer_->MatchQuotationMarks();
		if (this->lexer_->HasIdentity()) {
			shared_ptr <VarRef> rhs_ = shared_ptr <VarRef>(new VarRef(ValType::kVarName, this->lexer_->MatchIdentity()));
			return rhs_;
		}
		else {
			throw SyntaxError("Select statement - [suchthatcl] - invalid identity token inside quotes");
		}

	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - invalid token on RHS of relRef ");
	}
}


vector <shared_ptr<Pattern>> QueryBuilder::ParsePatterns() {
	vector<shared_ptr<Pattern>> patterns;

	lexer_->MatchPatternKeyword();
	
	patterns.push_back(ParsePattern());

	while (lexer_->HasAndKeyword()) {
		lexer_->MatchAndKeyword();
		patterns.push_back(ParsePattern());
	}

	return patterns;
}

shared_ptr<Pattern> QueryBuilder::ParsePattern() {
	shared_ptr<Pattern> pattern;

	string syn_name = lexer_->MatchIdentity();

	lexer_->MatchLeftBrace();

	// call GetDeclaredSyn() after MatchOpeningBrace to detect syntax error first
	shared_ptr<Ref> synonym = GetDeclaredSyn(syn_name);
	RefType ref_type = synonym->GetRefType();

	shared_ptr<VarRef> var_ref = ParseVarRef();
	lexer_->MatchComma();
	if (ref_type == RefType::kAssignRef) {
		shared_ptr<ExprSpec> expression = ParseExpression();
		pattern = shared_ptr<AssignPattern>(new AssignPattern(std::dynamic_pointer_cast<AssignRef>(synonym), var_ref, expression));
	}
	else if (ref_type == RefType::kIfRef) {
		lexer_->MatchUnderScore();
		lexer_->MatchComma();
		lexer_->MatchUnderScore();
		pattern = shared_ptr<IfPattern>(new IfPattern(std::dynamic_pointer_cast<IfRef>(synonym), var_ref));
	}
	else if (ref_type == RefType::kWhileRef) {
		lexer_->MatchUnderScore();
		pattern = shared_ptr<WhilePattern>(new WhilePattern(std::dynamic_pointer_cast<WhileRef>(synonym), var_ref));
	}
	else {
		throw SemanticError("The synonym in Pattern must be an assign or if or while synonym");
	}

	lexer_->MatchRightBrace();

	return pattern;
}

shared_ptr<ExprSpec> QueryBuilder::ParseExpression() {
	bool is_partial_expr = false;
	if (lexer_->HasUnderScore()) {
		lexer_->MatchUnderScore();
		is_partial_expr = true;

		if (lexer_->HasRightBrace()) {
			return shared_ptr<ExprSpec>(new WildcardExprSpec());
		}
	}
	
	lexer_->MatchQuotationMarks();
	
	string expr_str = GetExpressionStr();

	lexer_->MatchQuotationMarks();

	if (is_partial_expr) {
		lexer_->MatchUnderScore();

	}
	
	if (is_partial_expr) {
		return shared_ptr<PartialExprSpec>(new PartialExprSpec(expr_str));
	}
	else {
		return shared_ptr<ExactExprSpec>(new ExactExprSpec(expr_str));
	}

}

string QueryBuilder::GetExpressionStr() {
	string expr_str = "";
	int expected_closing_brace_num = 0;

	// make sure the expression is not empty;
	
	bool isExpectingToken = true;

	while (isExpectingToken) {
		while (lexer_->HasLeftBrace()) {
			lexer_->MatchLeftBrace();
			expr_str += "(";
			expected_closing_brace_num++;
		}

		if (lexer_->HasInteger()) {
			int integer = lexer_->MatchInteger();
			expr_str += std::to_string(integer);
		}
		else if (lexer_->HasIdentity()) {
			string identity = lexer_->MatchIdentity();
			expr_str += identity;
		}
		else {
			throw SyntaxError("A number or variable is expected in Assign clause");
		}

		while (lexer_->HasRightBrace()) {
			lexer_->MatchRightBrace();
			expr_str += ")";
			expected_closing_brace_num--;
			if (expected_closing_brace_num < 0) {
				throw SyntaxError("The opening and closing braces do not match");
			}
		}

		if (lexer_->HasOperator()) {
			string operator_str = lexer_->MatchOperator();
			expr_str += operator_str;
		}
		else {
			isExpectingToken = false;
		}

	}
	if (expected_closing_brace_num != 0) {
		throw SyntaxError("The opening and closing braces do not match");
	}

	return expr_str;
}


std::vector<shared_ptr<With>> QueryBuilder::ParseWithClauses() {
	vector<shared_ptr<With>> with_clauses;
	lexer_->MatchWithKeyword();
	with_clauses.push_back(ParseWithClause());

	while (lexer_->HasAndKeyword()) {
		lexer_->MatchAndKeyword();
		with_clauses.push_back(ParseWithClause());
	}

	return with_clauses;
}

shared_ptr<With> QueryBuilder::ParseWithClause() {
	shared_ptr<Ref> lhs = ParseWithRef();
	lexer_->MatchEqualSign();
	shared_ptr<Ref> rhs = ParseWithRef();

	// make sure if one reference is attrRef, it is on left hand side
	if (rhs->GetValType() == ValType::kInt || rhs->GetValType() == ValType::kString) {
		return std::make_shared<With>(lhs, rhs);
	}
	else {
		return std::make_shared<With>(rhs, lhs);
	}
}

shared_ptr<Ref> QueryBuilder::ParseWithRef() {
	if (lexer_->HasInteger()) {
		int integer = lexer_->MatchInteger();
		return std::make_shared<TempRef>(ValType::kInt, std::to_string(integer));
	}

	if (lexer_->HasQuotationMarks()) {
		lexer_->MatchQuotationMarks();
		string identity = lexer_->MatchIdentity();
		lexer_->MatchQuotationMarks();
		return std::make_shared<TempRef>(ValType::kString, identity);
	}

	// parse attribute reference
	string ref_name = lexer_->MatchIdentity();
	lexer_->MatchFullStop();
	string attr_name = lexer_->MatchAttrName();

	shared_ptr<Ref> synonym = GetDeclaredSyn(ref_name);

	ValidateAttrName(synonym, attr_name);

	return synonym;
}

void QueryBuilder::ValidateAttrName(shared_ptr<Ref> synonym, string attr_name) {
	string proc_name = "procName";
	string var_name = "varName";
	string value_str = "value";
	string stmt = "stmt#";

	const std::unordered_map<RefType, string> ref_type_to_attr_name_map{
		{RefType::kProcRef, proc_name},
		{RefType::kCallRef, proc_name},
		{RefType::kVarRef, var_name},
		{RefType::kReadRef, var_name},
		{RefType::kPrintRef, var_name},
		{RefType::kConstRef, value_str},
		{RefType::kStmtRef, stmt},
		{RefType::kReadRef, stmt},
		{RefType::kPrintRef, stmt},
		{RefType::kCallRef, stmt},
		{RefType::kWhileRef, stmt},
		{RefType::kIfRef, stmt},
		{RefType::kAssignRef, stmt}
	};

	if (ref_type_to_attr_name_map.at(synonym->GetRefType()) != attr_name) {
		throw SemanticError("The synonym " + synonym->GetName() + " has a wrong attribute name " + attr_name);
	}
}






