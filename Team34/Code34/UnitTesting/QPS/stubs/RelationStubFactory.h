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
	std::shared_ptr<std::vector<std::shared_ptr<ModifiesPRel>>> GetModifiesPRelStubs();
	std::shared_ptr<std::vector<std::shared_ptr<ModifiesSRel>>> GetModifiesSRelStubs();

	std::shared_ptr<std::vector<std::shared_ptr<UsesPRel>>> GetUsesPRelStubs();
	std::shared_ptr<std::vector<std::shared_ptr<UsesSRel>>> GetUsesSRelStubs();

	std::shared_ptr<std::vector<std::shared_ptr<FollowsRel>>> GetFollowsRelStubs();
	std::shared_ptr<std::vector<std::shared_ptr<FollowsTRel>>> GetFollowsTRelStubs();

	std::shared_ptr<std::vector<std::shared_ptr<ParentRel>>> GetParentRelStubs();
	std::shared_ptr<std::vector<std::shared_ptr<ParentTRel>>> GetParentTRelStubs();
};