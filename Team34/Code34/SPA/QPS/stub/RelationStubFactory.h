#pragma once

#include <vector>
#include <memory>

#include "../clause/relation/ModifiesPRel.h"
#include "../clause/relation/ModifiesSRel.h"
#include "../clause/relation/UsesPRel.h"
#include "../clause/relation/UsesSRel.h"
#include "../clause/relation/FollowsRel.h"
#include "../clause/relation/FollowsTRel.h"
#include "../clause/relation/ParentRel.h"
#include "../clause/relation/ParentTRel.h"

class RelationStubFactory {

public:
	/*
		procedure func1 {
			read x;
		}
	*/
	std::shared_ptr<Rel> GetModifiesP_proc_name_var_name();
	std::shared_ptr<Rel> GetModifiesP_proc_name_var_syn();
	std::shared_ptr<Rel> GetModifiesP_proc_syn_var_name();
	std::shared_ptr<Rel> GetModifiesP_proc_syn_var_syn();
	std::shared_ptr<Rel> GetModifiesP_proc_name_var_wildcard();
	std::shared_ptr<Rel> GetModifiesP_proc_syn_var_wildcard();

	/*
		5  x = y + 1;
	*/
	std::shared_ptr<Rel> GetModifiesS_stmt_num_var_name();
	std::shared_ptr<Rel> GetModifiesS_stmt_num_var_syn();
	std::shared_ptr<Rel> GetModifiesS_stmt_syn_var_name();
	std::shared_ptr<Rel> GetModifiesS_stmt_syn_var_syn();
	std::shared_ptr<Rel> GetModifiesS_stmt_num_var_wildcard();
	std::shared_ptr<Rel> GetModifiesS_stmt_syn_var_wildcard();

	/*
		procedure func2 {
			print y;
		}
	*/
	std::shared_ptr<Rel> GetUsesP_proc_name_var_name();
	std::shared_ptr<Rel> GetUsesP_proc_name_var_syn();
	std::shared_ptr<Rel> GetUsesP_proc_syn_var_name();
	std::shared_ptr<Rel> GetUsesP_proc_syn_var_syn();
	std::shared_ptr<Rel> GetUsesP_proc_name_var_wildcard();
	std::shared_ptr<Rel> GetUsesP_proc_syn_var_wildcard();

	/*
		5  x = y + 1
	*/
	std::shared_ptr<Rel> GetUsesS_stmt_num_var_name();
	std::shared_ptr<Rel> GetUsesS_stmt_num_var_syn();
	std::shared_ptr<Rel> GetUsesS_stmt_syn_var_name();
	std::shared_ptr<Rel> GetUsesS_stmt_syn_var_syn();
	std::shared_ptr<Rel> GetUsesS_stmt_num_var_wildcard();
	std::shared_ptr<Rel> GetUsesS_stmt_syn_var_wildcard();

	/*
		1  while(x < 2) {
		2    x = y + 2
		3    if(x < 2) {
		4	    x = z + 2
			 } else {
		5	    x = z - 2
			 }
		6	 z = 5
		   }
		
		Parent(1,2), Parent(1,3), Parent(1,6), Parent(3,4), Parent(3,5) 
		ParentT(1,2), ParentT(1,3), ParentT(1,6), ParentT(3,4), ParentT(3,5), ParentT(1, 4), ParentT(1,5)
		Follows(2,3), Follows(3,6), 
		FollowsT(2,3), FollowsT(3,6), FollowsT(2,6)
	*/

	// Use Follows(2,3) for all Follows relation stub
	std::shared_ptr<Rel> GetFollows_stmt_num_stmt_num();
	std::shared_ptr<Rel> GetFollows_stmt_num_stmt_syn();
	std::shared_ptr<Rel> GetFollows_stmt_syn_stmt_num();
	std::shared_ptr<Rel> GetFollows_stmt_syn_stmt_syn();
	std::shared_ptr<Rel> GetFollows_stmt_wildcard_stmt_num();
	std::shared_ptr<Rel> GetFollows_stmt_wildcard_stmt_syn();
	std::shared_ptr<Rel> GetFollows_stmt_num_stmt_wildcard();
	std::shared_ptr<Rel> GetFollows_stmt_syn_stmt_wildcard();
	std::shared_ptr<Rel> GetFollows_stmt_wildcard_stmt_wildcard();

	// Use FollowsT(2,6) for all FollowsT relation stub
	std::shared_ptr<Rel> GetFollowsT_stmt_num_stmt_num();
	std::shared_ptr<Rel> GetFollowsT_stmt_num_stmt_syn();
	std::shared_ptr<Rel> GetFollowsT_stmt_syn_stmt_num();
	std::shared_ptr<Rel> GetFollowsT_stmt_syn_stmt_syn();
	std::shared_ptr<Rel> GetFollowsT_stmt_wildcard_stmt_num();
	std::shared_ptr<Rel> GetFollowsT_stmt_wildcard_stmt_syn();
	std::shared_ptr<Rel> GetFollowsT_stmt_num_stmt_wildcard();
	std::shared_ptr<Rel> GetFollowsT_stmt_syn_stmt_wildcard();
	std::shared_ptr<Rel> GetFollowsT_stmt_wildcard_stmt_wildcard();

	// Use Parent(1,2) for all Parent relation stub
	std::shared_ptr<Rel> GetParent_stmt_num_stmt_num();
	std::shared_ptr<Rel> GetParent_stmt_num_stmt_syn();
	std::shared_ptr<Rel> GetParent_stmt_syn_stmt_num();
	std::shared_ptr<Rel> GetParent_stmt_syn_stmt_syn();
	std::shared_ptr<Rel> GetParent_stmt_wildcard_stmt_num();
	std::shared_ptr<Rel> GetParent_stmt_wildcard_stmt_syn();
	std::shared_ptr<Rel> GetParent_stmt_num_stmt_wildcard();
	std::shared_ptr<Rel> GetParent_stmt_syn_stmt_wildcard();
	std::shared_ptr<Rel> GetParent_stmt_wildcard_stmt_wildcard();

	// Use ParentT(1,4) for all ParentT relation stub
	std::shared_ptr<Rel> GetParentT_stmt_num_stmt_num();
	std::shared_ptr<Rel> GetParentT_stmt_num_stmt_syn();
	std::shared_ptr<Rel> GetParentT_stmt_syn_stmt_num();
	std::shared_ptr<Rel> GetParentT_stmt_syn_stmt_syn();
	std::shared_ptr<Rel> GetParentT_stmt_wildcard_stmt_num();
	std::shared_ptr<Rel> GetParentT_stmt_wildcard_stmt_syn();
	std::shared_ptr<Rel> GetParentT_stmt_num_stmt_wildcard();
	std::shared_ptr<Rel> GetParentT_stmt_syn_stmt_wildcard();
	std::shared_ptr<Rel> GetParentT_stmt_wildcard_stmt_wildcard();
};