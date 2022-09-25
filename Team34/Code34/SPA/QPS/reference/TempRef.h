#include "Ref.h"
#include "../../Utils/type/RefType.h"

class TempRef : public Ref {
	using Ref::Ref;

public:
	const RefType GetRefType() override { return RefType::kUnknown; }
};
