#include <vector>
#include <memory>

#include "../../../SPA/QPS/relation/ModifiesPRel.h"
#include "../../../SPA/QPS/relation/ModifiesSRel.h"
#include "../../../SPA/QPS/relation/UsesPRel.h"
#include "../../../SPA/QPS/relation/UsesSRel.h"
#include "../../../SPA/QPS/relation/FollowsRel.h"
#include "../../../SPA/QPS/relation/FollowsTRel.h"
#include "../../../SPA/QPS/relation/ParentRel.h"
#include "../../../SPA/QPS/relation/ParentTRel.h"

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
};