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
#include "..\relation\Rel.h"
#include "..\relation\FollowsRel.h"
#include "..\relation\FollowsTRel.h"
#include "..\relation\ParentRel.h"
#include "..\relation\ParentTRel.h"
#include "..\relation\UsesSRel.h"
#include "..\relation\UsesPRel.h"
#include "../pattern/Pattern.h"
#include "../pattern/AssignPattern.h"
#include "../pattern/IfPattern.h"
#include "../pattern/WhilePattern.h"

using std::shared_ptr;


QueryBuilder::QueryBuilder() {
	lexer_ = std::make_shared<QueryLexer>();
}

shared_ptr<Query> QueryBuilder::GetQuery(const std::string& query_string_) {
		this->lexer_->FeedQuery(query_string_);
		
		synonyms_ = ParseDeclarationStatements();
		
		shared_ptr<Query> query_ = ParseSelectStatement();
		std::shared_ptr<Query> sp_ = std::shared_ptr<Query>(query_);
		return sp_;
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

		while (lexer_->HasCommaDelimeter()) {
			lexer_->MatchCommaDelimeter();
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

	if (this->lexer_->HasKeyword("Select")) {
		this->lexer_->MatchKeyword("Select");
		std::vector<shared_ptr<Ref>> select_tuple_ = ParseReturnValues();

		std::vector<shared_ptr<Rel>> relations_;
		std::vector<shared_ptr<Pattern>> patterns_;
		while (lexer_->HasPatternKeyword() || HasSuchThatClause()) {
			
			if (lexer_->HasPatternKeyword()) {
				std::vector<shared_ptr<Pattern>> patterns = ParsePatterns();
				patterns_.insert(patterns_.end(), patterns.begin(), patterns.end());

			}
			else if (HasSuchThatClause()) {
				std::vector<shared_ptr<Rel>> relations = ParseRelations();
				// append new relations to the end of all relations
				relations_.insert(relations_.end(), relations.begin(), relations.end());
			}
		}
		
		//
		//if (lexer_->HasPatternKeyword()) {
		//	std::vector<shared_ptr<Pattern>> patterns_ = ParsePatterns();
		//}
		//

		if (this->lexer_->HasMoreTokens()) {
			throw SyntaxError("Unexpected token at end of query");
		}

		std::shared_ptr<std::vector<std::shared_ptr<Ref>>> select_tuple_s_ = std::make_shared<std::vector<std::shared_ptr<Ref>>>();
		for (shared_ptr<Ref> ref_ : select_tuple_) {
			std::shared_ptr <Ref> ref_s_ = std::shared_ptr<Ref>(ref_);
			select_tuple_s_->push_back(ref_s_);
		}

		std::shared_ptr <std::vector<std::shared_ptr<Rel>>> relations_s_ = std::make_shared<std::vector<std::shared_ptr<Rel>>>();
		for (shared_ptr<Rel> rel_ : relations_) {
			std::shared_ptr <Rel> rel_s_ = std::shared_ptr<Rel>(rel_);
			relations_s_->push_back(rel_s_);
		}

		std::shared_ptr < std::vector<std::shared_ptr<Pattern>>> patterns_s_ = std::make_shared<std::vector<std::shared_ptr<Pattern>>>();
		for (shared_ptr<Pattern> pattern_ : patterns_) {
			std::shared_ptr <Pattern> pattern_s_ = std::shared_ptr<Pattern>(pattern_);
			patterns_s_->push_back(pattern_s_);
		}

		shared_ptr<Query> query = shared_ptr<Query>(new Query(select_tuple_s_, relations_s_, patterns_s_));
		return query;
	}
	else {
		throw SyntaxError("Select Statment - Missing (select) keyword");
	}
}

std::vector<shared_ptr<Ref>> QueryBuilder::ParseReturnValues() {
	std::vector<shared_ptr<Ref>> select_tuple_;

	if (this->lexer_->HasIdentity()) {
		std::string identity_ = this->lexer_->MatchIdentity();

		for (shared_ptr<Ref> ref : synonyms_) {
			if (ref->GetName().compare(identity_) == 0) {
				select_tuple_.push_back(ref);
			}
		}

		if (select_tuple_.size() == 1) {
			return select_tuple_;
		}
		else {
			throw SemanticError("Select Statement - Synonym " + identity_ + " used without declaration first");
		}

	}
	else {
		throw SyntaxError("Select Statement - Missing synonyms to be returned");
	}
}

bool QueryBuilder::HasSuchThatClause() {
	return lexer_->HasKeyword("such") && (lexer_->PeekNextToken(1) == "that");
}

std::vector<shared_ptr<Rel>> QueryBuilder::ParseRelations() {
	std::vector<shared_ptr<Rel>> relations;
	if (!HasSuchThatClause()) {
		return relations;
	}
	lexer_->MatchKeyword("such");
	lexer_->MatchKeyword("that");

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

	lexer_->MatchOpeningBrace();

	shared_ptr<Rel> relation = ParseRelRefClause(relation_name);

	lexer_->MatchClosingBrace();

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
	auto [lhs_syn, rhs_syn] = GetParentOrFollowsSyns();
	return shared_ptr<Rel>(new FollowsRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseFollowsTRel() {
	auto [lhs_syn, rhs_syn] = GetParentOrFollowsSyns();
	return shared_ptr<Rel>(new FollowsTRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseParentRel() {
	auto [lhs_syn, rhs_syn] = GetParentOrFollowsSyns();
	return shared_ptr<Rel>(new ParentRel(lhs_syn, rhs_syn));
}

shared_ptr<Rel> QueryBuilder::ParseParentTRel() {
	auto [lhs_syn, rhs_syn] = GetParentOrFollowsSyns();
	return shared_ptr<Rel>(new ParentTRel(lhs_syn, rhs_syn));
}


std::pair<shared_ptr<Ref>, shared_ptr<VarRef>> QueryBuilder::GetModifiesOrUsesSyns() {
	shared_ptr<Ref> lhs_syn;
	shared_ptr<VarRef> rhs_syn;
	
	if (lexer_->HasUnderScore()) {
		throw SemanticError("The first EntRef in Modifies and Uses relation cannot be WildCard");
	}

	if (lexer_->HasIdentity()) {
		string ref_name = lexer_->MatchIdentity();
		//lhs_syn = std::dynamic_pointer_cast<StmtRef>(GetDeclaredSyn(ref_name, RefType::kStmtRef));
		lhs_syn = GetDeclaredSyn(ref_name);
		if (lhs_syn->GetRefType() != RefType::kProcRef && lhs_syn->GetRefType() != RefType::kStmtRef
			&& !stmt_ref_types.count(lhs_syn->GetRefType())) {
			throw SemanticError("Type of synonym " + lhs_syn->GetName() + " is unmatched to declared type");
		}

	} 
	else if (lexer_->HasInteger()) {
		lhs_syn = GetNextStmtRef();
	}
	else {
		lhs_syn = GetNextProcRef();
	}

	lexer_->MatchCommaDelimeter();

	rhs_syn = GetNextVarRef();
	return { lhs_syn, rhs_syn };
}

std::pair<shared_ptr<StmtRef>, shared_ptr<StmtRef>> QueryBuilder::GetParentOrFollowsSyns() {
	shared_ptr<StmtRef> lhs_syn = GetNextStmtRef();
	lexer_->MatchCommaDelimeter();
	shared_ptr<StmtRef>rhs_syn = GetNextStmtRef();
	return { lhs_syn, rhs_syn };
}


shared_ptr<StmtRef> QueryBuilder::GetNextStmtRef() {
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

shared_ptr<ProcRef> QueryBuilder::GetNextProcRef() {
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

shared_ptr<VarRef> QueryBuilder::GetNextVarRef() {
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
	if (this->lexer_->HasCommaDelimeter()) {
		this->lexer_->MatchCommaDelimeter();
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


std::vector <shared_ptr<Pattern>> QueryBuilder::ParsePatterns() {
	std::vector<shared_ptr<Pattern>> patterns;

	lexer_->MatchPatternKeyword();
	
	patterns.push_back(ParsePattern());

	while (lexer_->HasAndKeyword()) {
		lexer_->MatchAndKeyword();
		patterns.push_back(ParsePattern());
	}

	return patterns;
}

shared_ptr<Pattern> QueryBuilder::ParsePattern() {
	string syn_name = lexer_->MatchIdentity();

	lexer_->MatchOpeningBrace();
	shared_ptr<VarRef> var_ref = GetNextVarRef();
	lexer_->MatchCommaDelimeter();
	shared_ptr<ExprSpec> expression = GetNextExpression();
	lexer_->MatchClosingBrace();

	shared_ptr<Ref> synonym = GetDeclaredSyn(syn_name);

	if (synonym->GetRefType() != RefType::kAssignRef) {
		throw SemanticError("The synonym in Pattern must be an assign synonym");
	}
	shared_ptr<Pattern> pattern = shared_ptr<AssignPattern>(new AssignPattern(std::dynamic_pointer_cast<AssignRef>(synonym), var_ref, expression));

	return pattern;
}

shared_ptr<ExprSpec> QueryBuilder::GetNextExpression() {
	bool is_partial_expr = false;
	if (lexer_->HasUnderScore()) {
		lexer_->MatchUnderScore();
		is_partial_expr = true;

		if (lexer_->HasClosingBrace()) {
			return shared_ptr<ExprSpec>(new WildcardExprSpec());
		}
		
	}
	
	lexer_->MatchQuotationMarks();
	
	string expr_str = GetExpression();

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


string QueryBuilder::GetExpression() {
	string expr_str = "";
	int expected_closing_brace_num = 0;

	// make sure the expression is not empty;
	
	bool isExpectingToken = true;

	while (isExpectingToken) {
		while (lexer_->HasOpeningBrace()) {
			lexer_->MatchOpeningBrace();
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

		while (lexer_->HasClosingBrace()) {
			lexer_->MatchClosingBrace();
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


